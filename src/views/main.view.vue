<template>
    <div class="main">

        <h1 id="maintitle">WASM Benchmark</h1>

        <!-- generate option picker -->
        <VOptionPicker 
            :name="'benchmarks'" 
            :ids="[...optIds]" 
            :values="[...optNames]"
            @select="handleSelect"
        ></VOptionPicker>

        <br/>

        <!-- generate benchmark content -->
        <div v-for="(val, idx) in config" v-bind:key="idx">
            
            <!-- apply animate.css class here if needed -->
            <div class="container animated" v-if="val.id === benchmark">
                
                <h2>{{ val.label }}</h2>
                <div v-if="val.note" :class="`note-${val.id}`" v-html="val.note"></div>
                <div class="bench-wrap" :id="val.id" v-for="(_val, _idx) in val.fields" v-bind:key="_idx">
                        
                    <!-- textfield content component -->
                    <VInput
                        v-if="_val.type === 'text'"
                        :label="_val.label"
                        :name="_val.name"
                        :placeholder="_val.placeholder"
                        @change="handleChange"
                    >
                    </VInput>

                    <!-- button content component -->
                    <VButton
                        v-if="_val.type === 'button'"
                        :name="_val.name"
                        :label="_val.label"
                        :flags="['generic']"
                        @press="invokeCallback(_val.callback)"
                    >
                    </VButton>

                    <!-- canvas content component -->
                    <VCanvas v-if="_val.type === 'canvas'" 
                        :id="'screen'" 
                        :width="'268'"
                    >
                    </VCanvas>

                    <!-- fallback content component -->
                    <div v-if="!_val.type" v-html="generated"></div>

                </div>
                
                <br/>
                
                <!-- benchmark executing button -->
                <VButton
                    v-if="!val.norun"
                    :name="benchmark"
                    :label="'Run'"
                    @press="handlePress"
                ></VButton>

            </div>
            
        </div>

        <!-- content expanding component -->
        <div class="content-expand"></div>

        <!-- benchmark result container -->
        <transition name="fade">
            <div class="results" v-if="times.js">
                
                <div class="lang" id="c">
                    <span>C</span> benchmark ran in {{ times.c }} seconds. ({{ times.diff }}% {{ times.kword }})
                </div>

                <div class="lang" id="js">
                    <span>JS</span> benchmark ran in {{ times.js }} seconds.
                </div>
            </div>
        </transition>

    </div>
</template>

<script lang="ts">

    import { Component, Vue } from 'vue-property-decorator';
    import VOptionPicker from '@/components/option.component.vue';
    import VInput from '@/components/input.component.vue';
    import VButton from '@/components/button.component.vue';
    import VCanvas from '@/components/canvas.component.vue';
    import appConfig from '@/configurations/app.config';
    import aliasConfig from '@/configurations/alias.config';
    import { compositeDataCarry, APIConsumer } from '@/structures/types.struct';
    import Dynamics from '@/modules/dynamics.module';
    import { AutoImplement } from '@/structures/decorators.struct';
    import API from '@/modules/api.module';
    import jfc from '@/jfc';

    @AutoImplement(['APIConsumer'])
    @Component({
        components: {
            VOptionPicker,
            VInput,
            VButton,
            VCanvas,
        },
    })
    export default class Main extends Vue implements APIConsumer {

        public postman!: API;

        private optNames: string[] = appConfig.map((val) => (val as any).label);
        private optIds: string[] = appConfig.map((val) => (val as any).id);
        private config: object[] = appConfig;
        private aliases: any = aliasConfig;
        private benchmark: string = '';
        private inputValues: any = {};
        private times: any = {c: null, js: null, diff: null, kword: null};
        private generated: string = '';
        private animationFrameId: any = 0;
        private localAddressStack: any[] = [];

        /**
         * Invoke callbacks after button click.
         *
         * @param callback - Callback name
         */
        private invokeCallback(callback: string) {
            Dynamics.invoke(this, callback);
        }

        /**
         * VOptionPicker selection handler.
         *
         * @param value - Selected value
         */
        private handleSelect(val: string) {

            this.benchmark = val;

            (window as any).cancelAnimationFrame(this.animationFrameId);
            this.freeAddresses();

            if (val.includes('selfexec')) {
                this.invokeSelfExecutables();
            }
        }

        /**
         * VInput value change handler.
         *
         * @param val - New value
         */
        private handleChange(val: string) {
            const split: any[] = val.split('=');
            this.inputValues[`${this.benchmark}.${split[0]}`] = parseInt(split[1], 10);
        }

        /**
         * Execute preformance test and measure delta by substracting
         * time of function execution finish and time of function
         * exectuion invokation.
         *
         * @param callback - Callback to execute
         * @returns Time in seconds
         */
        private perf(callback: (...args: any) => number): number {

            const t1: number = performance.now();
            const result = callback(...this.sniffParams());
            const t2: number = performance.now();

            const diff =  (t2 - t1) / 1000;

            this.pushAddresses(result);

            return diff;
        }

        /**
         * Sniff parameters from configuration to pass into
         * perf callback function.
         *
         * @returns Array of params
         */
        private sniffParams(): any[] {
            return Object.keys(this.inputValues)
                .sort()
                .filter((val) => val.includes(this.benchmark)).map((val) => this.inputValues[val]);
        }

        /**
         * Handler for execution button clicking which starts
         * performance measuring routines.
         *
         * @param val - Identifier of button
         */
        private handlePress(val: string) {

            if (val.includes('noperf')) {
                (this as any)[this.aliases.js[val]]();
                return;
            }

            const translate: string[] = [this.aliases.c[this.benchmark], this.aliases.js[this.benchmark]];
            const cTime: number = this.perf((this as any).module[translate[0]]);
            const jsTime: number = this.perf((jfc as any)[translate[1]]);

            this.sendResultsToStorage(cTime, jsTime);

            this.times.c = cTime;
            this.times.js = jsTime;

            const [less, more] = [cTime, jsTime].sort();
            this.times.diff = (((more / less) - 1) * 100).toFixed(3);
            this.times.kword = (cTime < jsTime ? 'faster' : 'slower');
        }

        /**
         * This function finds names of self executable
         * callbacks from configuration and executes them
         * with no parameters. It is used when we need to load
         * some data asynchronously after using VOptionPicker.
         */
        private invokeSelfExecutables() {

            const keys: string[] = Object.keys(this.aliases.js);

            keys.forEach((val) => {
                if (val.includes('selfexec')) {
                    this.invokeCallback(this.aliases.js[val]);
                }
            });
        }

        /**
         * This callback is dynamically called from noperf invoking
         * call chain. It animates canvas based on parameters.
         */
        private setCanvas() {

            const canvas: any = document.getElementById('screen');
            const context = canvas.getContext('2d');

            (window as any).cancelAnimationFrame(this.animationFrameId);

            const addr: number = (this as any).module._canvas_init(canvas.width, canvas.height, this.sniffParams()[0]);
            this.pushAddresses(addr);
            this.renderPointsFromOffset(addr, canvas, context);
        }

        /**
         * Get all point structures from memory offset and
         * render them in the canvas.
         *
         * @param address - Start offset of structure array
         * @param canvas - Canvas DOM element reference
         * @param contex - Context object reference
         */
        private renderPointsFromOffset(address: number, canvas: any, context: any) {

            const itemAmount = (window as any).getValue(address, 'i32');
            const itemSize = (window as any).getValue(address + 4, 'i32');
            const directAddress = (window as any).getValue(address + 8, '*');

            context.clearRect(0, 0, canvas.width, canvas.height);

            for (let i = directAddress; i < directAddress + itemAmount * itemSize; i += itemSize) {

                const [x, y] = [(window as any).getValue(i, 'double'), (window as any).getValue(i + 8, 'double')];

                context.beginPath();
                context.arc(x, y, 1, 0, 2 * Math.PI, false);
                context.fillStyle = 'yellow';
                context.fill();
            }

            (this as any).module._canvas_move();

            this.animationFrameId = window.requestAnimationFrame( () => {
                this.renderPointsFromOffset(address, canvas, context);
            });
        }

        /**
         * Sniff if perf callback used any heap memory. If it did,
         * push it to address stack, because addresses need to be
         * later released.
         *
         * @param value - Anything returned from perf callback
         */
        private pushAddresses(value: any) {

            if (this.benchmark.includes('memconsume')) {
                if (typeof value === 'number') {
                    this.localAddressStack[0] = value;
                    this.localAddressStack[1] = (window as any).getValue(value + 8, '*');
                }
            }
        }

        /**
         * Free addresses from localAddressStack.
         */
        private freeAddresses() {

            this.localAddressStack.forEach ((val) => {
                (this as any).module._free(val);
            });

            this.localAddressStack = [];
        }

        /**
         * Send data to public API.
         *
         * @param cTime - C performance time to store
         * @param jsTime - JS perfomance time to store
         */
        private async sendResultsToStorage(cTime: number, jsTime: number) {
            const requestResult = await this.postman.feed({key: 'wasmb'}).request('getWasmb');

            const dataArr = JSON.parse(requestResult.data.shape);
            dataArr.push({benchmark: this.benchmark, cTime, jsTime});

            const updated: compositeDataCarry = {key: 'wasmb', value: JSON.stringify(dataArr)};
            await this.postman.feed(updated).request('setWasmb');
        }
    }

</script>

<style lang="scss">

    .content-expand {
        height: 80px;
        width: 100px;
    }

    .container {
        padding-bottom: 20px;
    }

    .fade-enter-active, .fade-leave-active {
        transition: opacity .5s;
    }

    .fade-enter, .fade-leave-to {
        opacity: 0;
    }

    h1 {
        color: $front-main;
        font-size: 2.5em;

        &#maintitle {
            padding-left: 60px;
            background-image: url('/img/icons/wasm.svg');
            background-repeat: no-repeat;
            background-position: 0px 0px;
            background-size: 43px 39px;
        }
    }

    h2 {
        color: $front-main;
        text-decoration: underline;
    }

    .bench-wrap {
        &:not(:first-child) {
            margin-top: 1.5rem;
        }

        &[id*='selfexec_info'] {
            div div {
                display: block;
                font-size: $info-font-size;
                color: $wasm-front;
                margin-top: 0rem;
                display: flex;
                justify-content: space-between;
                width: 350px;
                align-items: center;
                
                &:not(:first-child) {
                    margin-top: 1rem;
                }

                > span {
                    width: 280px;
                    padding: 6px 6px;
                    border-radius: 5px;
                    text-align: center;
                    font-weight: bold;
                }

                > span:first-child {
                    background-color: $front-main;
                    color: $back-main;
                    margin-right: 1rem;
                }

                > span:not(:first-child) {
                    color: $wasm-front;
                    border: 2px solid $wasm-back;
                }
            }
        }
    }

    [class*="note"] {
        color: white;
        font-style: oblique;
        border-radius: 20px;
    }

    .results {
        position: fixed;
        right: 0;
        bottom: 0;
        width: 100%;
        
        .lang {
            padding: 10px;
            font-size: 1.1rem;
            overflow-x: hidden;
            text-overflow: ellipsis;
            right: 0;
            color: white;
            white-space: nowrap;
            text-align: center;
            font-weight: bold;

            span {
                background-color: $back-main;
                padding: 3px 5px;
                border-radius: 5px;
            }
        }

        #c {
            background: -webkit-linear-gradient(to right, #2196f3, #f44336);
            background: linear-gradient(to right, #2196f3, #f44336);
        }

        #js {
            background: -webkit-linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
            background: linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
        }
    }

</style>
