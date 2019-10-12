<template>
    <div class="option-picker">
        
        <div class="option-picker-wrap">
            
            <div class="item" 
                v-for="(val, idx) in values" 
                :id="ids[idx]" 
                @click="handleSelect($event)"
                v-bind:key="idx">
                {{ val }}
            </div>

        </div>

    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';

    @Component
    export default class OptionPicker extends Vue {

        @Prop() private name!: string;
        @Prop() private values!: string[];
        @Prop() private ids!: string[];

        private activeElement!: HTMLElement;


        /**
         * Select first element by default.
         *
         * @pipeType - modify internal state
         */

        private mounted() {
            this.handleSelect({
                currentTarget: document.getElementById(this.ids[0]),
            });
        }


        /**
         * Handle option selection and return
         * option unique identifier.
         *
         * @param {any} event - event object referent
         *
         * @return {string} - identifier of option
         */

        @Emit('select')
        private handleSelect(evt: any) {

            if (this.activeElement) {
                this.activeElement.classList.remove('active');
            }

            this.activeElement = evt!.currentTarget;
            this.activeElement.classList.add('active');
            return evt!.currentTarget!.id;
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
            color: #aaccff;
            border: 2px solid #aaccff;
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
                    border-right: 1px solid #aaccff;
                }

                &:hover {
                    color: white;
                    background: transparent;
                }

                &.active {
                    color: #222233;
                    background-color: #aaccff;
                }
            }    
        }
    }

</style>