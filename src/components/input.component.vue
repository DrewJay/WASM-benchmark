<template>
    <div class="v-input">
        
        <div class="v-input-wrap">
            
            <div class="v-input-label" :class="{focused}" v-if="label !== ''">{{ label }}</div>
            
            <input 
                type="text"
                @keyup="emitValue"
                @focus="handleFocus"
                @blur="handleBlur"
                :placeholder="placeholder"
            > 
            
        </div>

    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';
    import { Emitor } from '@/structures/types.struct';

    @Component
    export default class VInput extends Vue {

        @Prop() private name!: string;
        @Prop() private placeholder!: string[];
        @Prop() private label!: string;

        private focused: boolean = false;

        /**
         * Emit event when value changes.
         *
         * @param evt - Event object reference.
         * @returns Key value string pair
         */
        @Emit('change')
        public emitValue(evt: any) {
            return `${this.name}=${evt!.currentTarget!.value}`;
        }

        /**
         * Handle element focus.
         */
        private handleFocus() {
            this.focused = true;
        }

        /**
         * Handle element blur.
         */
        private handleBlur() {
            this.focused = false;
        }
    }

</script>

<style lang="scss" scoped>

    .v-input-wrap {

        .v-input-label {
            color: $wasm-front;
            font-weight: 700;
            font-size: $input-label-font-size;
            border: 3px solid $wasm-back;
            padding: .5rem 1rem .5rem 1rem;
            background-color: $back-main;
            margin-bottom: 0px;
            border-top-left-radius: 5px;
            border-top-right-radius: 5px;
            z-index: 9999;
            display: table;
            transition: color .3s, min-width .3s;
            transition-timing-function: linear;
            min-width: 0;
            border-bottom: none;

            &.focused {
                min-width: 235px; 
            }
        }

        input[type="text"] {
            background: transparent;
            border: 3px solid $front-main;
            border-bottom-left-radius: 5px;
            border-radius: 5px;
            padding: 8px;
            font-weight: bold;
            font-size: $input-font-size;
            color: $front-main;
            width: 250px;
            
            &::-webkit-input-placeholder {
                color: $front-main;
                font-style: oblique;
                font-size: $input-font-size;
                font-weight: 100;
            }
        }
    }

</style>