<template>
    <div class="home">

        <h1>WASM Benchmark</h1>

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
                <div class="lang" id="c"><span>C</span> benchmark ran in {{ times.c }} seconds.</div>
                <div class="lang" id="js"><span>JS</span> benchmark ran in {{ times.js }} seconds.</div>
            </div>
        </transition>

    </div>
</template>

<script lang="ts">

    import { Component, Vue } from 'vue-property-decorator';
    import OptionPicker from '@/components/OptionPicker.vue';
    import VInput from '@/components/VInput.vue';
    import VButton from '@/components/VButton.vue';
    import { benchmarkConfig, aliasConfig } from '@/views/config';
    import jfc from '@/jfc';

    @Component({
        components: {
            OptionPicker,
            VInput,
            VButton,
        },
    })

    export default class Home extends Vue {

        private optNames: string[] = benchmarkConfig.map((val) => (val as any).label);
        private optIds: string[] = benchmarkConfig.map((val) => (val as any).id);
        private config: object[] = benchmarkConfig;
        private aliases: any = aliasConfig;
        private benchmark: string = '';
        private values: any = {};
        private times: any = {c: null, js: null};
        private generated: string = '';


        /**
         * OptionPicker selection handler.
         *
         * @param {string} value - selected value
         */

        private handleSelect(val: string) {
            this.benchmark = val;

            if (val.includes('selfexec')) {
                this.invokeSelfExecutables();
            }
        }


        /**
         * VInput value change handler.
         *
         * @param {string} val - new value
         */

        private handleChange(val: string) {
            const split: any[] = val.split('=');
            this.values[`${this.benchmark}.${split[0]}`] = parseInt(split[1], 10);
        }


        /**
         * Execute preformance test and measure delta by substracting
         * time of function execution finish and time of function
         * exectuion invokation.
         *
         * @param {function} callback - callback to execute
         *
         * @return {number} - time in seconds
         */

        private perf(callback: (...args: any) => number): number {
            const t1: number = performance.now();
            callback(...this.sniffParams());
            const t2: number = performance.now();

            return (t2 - t1) / 1000;
        }


        /**
         * Sniff parameters from configuration to pass into
         * perf callback function.
         *
         * @return {Array} - array of params
         */

        private sniffParams(): any[] {
            return Object.keys(this.values).filter((val) => val.includes(this.benchmark)).map((val) => this.values[val]);
        }


        /**
         * Handler for execution button clicking which starts
         * performance measuring routines.
         *
         * @param {string} val - identifier of button
         */

        private handlePress(val: string) {

            const translate: string[] = [this.aliases.js[this.benchmark], this.aliases.c[this.benchmark]];
            const jsTime: number = this.perf((jfc as any)[translate[0]]);
            const cTime: number = this.perf((this as any).module[`${translate[1]}`]);

            this.times.js = jsTime;
            this.times.c = cTime;
        }


        /**
         * This function finds names of self executable
         * callbacks from configuration and executes them
         * with no parameters. It is used when we need to load
         * some data asynchronously after using OptionPicker.
         *
         * @pipeType - invokes callbacks
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
         *
         * @pipeType - modifies DOM
         */

        private setInfo() {
            const inst: any = (this as any);

            const length: any = inst.module.HEAP8.length;
            const offset: any = inst.module._get_heap_offset();

            this.generated =
                `<div><span>Total memory</span> <span>${length} bytes</span></div>
                <div><span>Heap offset</span> <span>${offset} bytes</span></div>
                <div><span>Usable memory</span> <span>${length - offset} bytes</span></div>
                <div><span>Alloc index</span> <span>~${(length - offset) / inst.module._get_size_factor()} itrs</span></div>`;
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
    }

    h2 {
        color: $front-main;
    }

    .bench-wrap {
        &:not(:first-child) {
            margin-top: 1.5rem;
        }

        &#noperf_selfexec_info {
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
        color: $front-main;
        font-style: oblique;
        border-radius: 20px;
    }

    .results {
        position: fixed;
        top: 100%;
        transform: translateY(-100%);
        width: 70%;
        right: 0;
        
        .lang {
            padding: 10px;
            font-size: 1.5rem;
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
