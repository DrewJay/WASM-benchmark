<template>
    <div class="home">

        <h1 id="maintitle">WASM Benchmark</h1>

        <!-- generate option picker -->
        <OptionPicker 
            :name="'benchmarks'" 
            :ids="[...optIds]" 
            :values="[...optNames]"
            @select="handleSelect"
        ></OptionPicker>

        <br/>

        <!-- generate benchmark content -->
        <div v-for="(val, idx) in config" v-bind:key="idx">
            
            <div class="fadeInUp animated" v-if="val.id === benchmark">
                
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

                    <!-- fallback content component -->
                    <div v-if="!_val.type" v-html="generated">
                    </div>

                    <VCanvas v-if="_val.type === 'canvas'" 
                        :id="'screen'" 
                        :width="'268'"
                    >
                    </VCanvas>

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
    import OptionPicker from '@/components/OptionPicker.vue';
    import VInput from '@/components/VInput.vue';
    import VButton from '@/components/VButton.vue';
    import VCanvas from '@/components/VCanvas.vue';
    import { benchmarkConfig, aliasConfig } from '@/views/config';
    import jfc from '@/jfc';

    @Component({
        components: {
            OptionPicker,
            VInput,
            VButton,
            VCanvas,
        },
    })

    export default class Home extends Vue {

        private optNames: string[] = benchmarkConfig.map((val) => (val as any).label);
        private optIds: string[] = benchmarkConfig.map((val) => (val as any).id);
        private config: object[] = benchmarkConfig;
        private aliases: any = aliasConfig;
        private benchmark: string = '';
        private inputValues: any = {};
        private times: any = {c: null, js: null, diff: null, kword: null};
        private generated: string = '';
        private animationFrameId: any = 0;
        private localAddressStack: any[] = [];

        /**
         * OptionPicker selection handler.
         *
         * @param {string} value selected value
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
         * @param {string} val new value
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
         * @param {function} callback callback to execute
         * @return {number} time in seconds
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
         * @return {Array} array of params
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
         * @param {string} val identifier of button
         */
        private handlePress(val: string) {

            if (val.includes('noperf')) {
                (this as any)[this.aliases.js[val]]();
                return;
            }

            const translate: string[] = [this.aliases.js[this.benchmark], this.aliases.c[this.benchmark]];
            const jsTime: number = this.perf((jfc as any)[translate[0]]);
            const cTime: number = this.perf((this as any).module[translate[1]]);

            this.times.js = jsTime;
            this.times.c = cTime;

            const [less, more] = [jsTime, cTime].sort();
            this.times.diff = ((more / less) * 100).toFixed(3);
            this.times.kword = (jsTime > cTime ? 'faster' : 'slower');
        }

        /**
         * This function finds names of self executable
         * callbacks from configuration and executes them
         * with no parameters. It is used when we need to load
         * some data asynchronously after using OptionPicker.
         */
        private invokeSelfExecutables() {

            const keys: string[] = Object.keys(this.aliases.js);

            keys.forEach((val) => {
                if (val.includes('selfexec')) {
                    (this as any)[this.aliases.js[val]]();
                }
            });
        }

        /**
         * This callback is dynamically called by invokeSelfExecutables
         * function and fills fallback div container with proper HTML.
         */
        private setInfo() {

            const inst: any = (this as any);

            const length: any = inst.module.HEAP8.length;
            const stackOffset: any = (window as any).STACK_MAX;

            this.generated =
                `<div><span>Total memory</span> <span>${length} bytes</span></div>
                <div><span>Heap offset</span> <span>${stackOffset} bytes</span></div>
                <div><span>Usable memory</span> <span>${length - stackOffset} bytes</span></div>
                <div><span>Alloc index</span> <span>~${(length - stackOffset) / inst.module._get_size_factor()} itrs</span></div>`;
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
         * @param {number} address start offset of structure array
         * @param {any} canvas canvas DOM element reference
         * @param {any} context context object reference
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
         * @param {any} value anything returned from perf callback
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
    }

</script>

<style lang="scss">

    .fade-enter-active, .fade-leave-active {
        transition: opacity .5s;
    }

    .fade-enter, .fade-leave-to {
        opacity: 0;
    }

    h1 {
        color: $front-main;

        &#maintitle {
            padding-left: 50px;
            background-image: url('/img/icons/wasm.svg');
            background-repeat: no-repeat;
            background-size: 35px 30px;
        }
    }

    h2 {
        color: $front-main;
    }

    .bench-wrap {
        &:not(:first-child) {
            margin-top: 1.5rem;
        }

        &#selfexec_info {
            div div {
                display: block;
                color: $front-main;
                margin-top: 0rem;
                display: flex;
                justify-content: space-between;
                width: 280px;
                align-items: center;
                
                &:not(:first-child) {
                    margin-top: 1rem;
                }

                > span:first-child {
                    background-color: $front-main;
                    color: $back-main;
                    padding: 6px 0px;
                    width: 150px;
                    font-weight: bold;
                    text-align: center;
                    margin-right: 1rem;
                    border-radius: 5px;
                }

                > span:not(:first-child) {
                    font-weight: bold;
                    border-top-left-radius: 5px;
                    color: $front-main;
                    border: 2px solid $front-main;
                    padding: 5px 0px;
                    width: 150px;
                    text-align: center;
                    border-radius: 5px;
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
        top: 100%;
        transform: translateY(-100%);
        width: 50%;
        right: 0;
        
        .lang {
            padding: 10px;
            font-size: 1rem;
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
            background: #2196f3;
            background: -webkit-linear-gradient(to right, #2196f3, #f44336);
            background: linear-gradient(to right, #2196f3, #f44336);
            border-top-left-radius: 5px;
        }

        #js {
            background: #12c2e9;
            background: -webkit-linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
            background: linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
        }
    }

    @-webkit-keyframes fadeInUp {
        from {
            opacity: 0;
            -webkit-transform: translate3d(0, 30%, 0);
            transform: translate3d(0, 30%, 0);
        }

        to {
            opacity: 1;
            -webkit-transform: translate3d(0, 0, 0);
            transform: translate3d(0, 0, 0);
        }
    }

    @keyframes fadeInUp {
        from {
            opacity: 0;
            -webkit-transform: translate3d(0, 30%, 0);
            transform: translate3d(0, 30%, 0);
        }

        to {
            opacity: 1;
            -webkit-transform: translate3d(0, 0, 0);
            transform: translate3d(0, 0, 0);
        }
    }

    .fadeInUp {
        -webkit-animation-name: fadeInUp;
        animation-name: fadeInUp;
    }

    .animated {
        -webkit-animation-duration: 1s;
        animation-duration: 1s;
        -webkit-animation-fill-mode: both;
        animation-fill-mode: both;
    }

</style>
