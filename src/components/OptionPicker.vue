<template>
    <div class="option-picker">
        
        <div class="option-picker-wrap">
            
            <div class="item" 
                v-for="(val, idx) in values" 
                :id="ids[idx]" 
                @click="emitValue($event)"
                v-bind:key="idx">
                {{ val }}
            </div>

        </div>

    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';
    import { Emitor } from './types';

    @Component
    export default class OptionPicker extends Vue implements Emitor {

        public activeElement!: HTMLElement|null;

        @Prop() private name!: string;
        @Prop() private values!: string[];
        @Prop() private ids!: string[];
        @Prop() private bind!: string[];

        /**
         * Handle option selection and return
         * option unique identifier.
         *
         * @param event - Event object referent
         * @returns Identifier of option
         */
        @Emit('select')
        public emitValue(evt: any) {

            this.accessAndDisableBoundComponents();

            if (this.activeElement) {
                this.activeElement.classList.remove('active');
            }

            this.activeElement = evt!.currentTarget;
            this.activeElement!.classList.add('active');
            return evt!.currentTarget!.id;
        }

        /**
         * Select first element by default.
         */
        private mounted() {
            this.emitValue({
                currentTarget: document.getElementById(this.ids[0]),
            });
        }

        /**
         * Access bound OptionPickers and disable them. This
         * creates functionality of entangled components.
         */
        private accessAndDisableBoundComponents() {

            if (!this.bind) { return; }

            this.bind.forEach((name) => {

                const component: any = this.$parent.$children.filter((val) => (val as any).name === name);

                if (component[0].activeElement) {
                    component[0]!.activeElement.classList.remove('active');
                }

            });
        }
    }

</script>

<style lang="scss" scoped>

    $borderRadius: 10px;

    .option-picker {
        
        .option-picker-wrap {    
            border-radius: $borderRadius;
            cursor: pointer;
            display: inline-block;
            box-shadow: 0 3px 6px rgba(0,0,0,0.16), 0 3px 6px rgba(0,0,0,0.23);
            color: $front-main;
            white-space: nowrap;
            border: 2px solid $front-main;
            font-weight: bold;
            overflow-x: hidden;
            background: #12c2e9;
            background: -webkit-linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
            background: linear-gradient(to right, #f64f59, #c471ed, #12c2e9);

            .item {
                display: inline-block;
                padding: 10px;
                background-color: $back-main;
                transition: background-color .3s, color .3s;

                &:not(:last-child) {
                    border-right: 1px solid $front-main;
                }

                &:hover {
                    color: white;
                    background: transparent;
                }

                &.active {
                    color: $back-main;
                    background-color: $front-main;
                }
            }    
        }
    }

</style>