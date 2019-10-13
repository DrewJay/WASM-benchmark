<template>
    <div class="v-input">
        
        <div class="v-input-wrap">
            
            <div class="v-input-label" :class="{focused}" v-if="label !== ''">{{ label }}</div>
            
            <input 
                type="text"
                @keyup="handleChange"
                @focus="handleFocus"
                @blur="handleBlur"
                :placeholder="placeholder"
            > 
            
        </div>

    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';

    @Component
    export default class VInput extends Vue {

        @Prop() private name!: string;
        @Prop() private placeholder!: string[];
        @Prop() private label!: string;

        private focused: boolean = false;


        /**
         * Emit event when value changes.
         *
         * @param {any} evt - event object reference.
         *
         * @return {string} - key value string pair
         */

        @Emit('change')
        private handleChange(evt: any) {
            return `${this.name}=${evt!.currentTarget!.value}`;
        }


        /**
         * Handle element focus.
         *
         * @pipeType - internally change focus state
         */

        private handleFocus() {
            this.focused = true;
        }


        /**
         * Handle element blur.
         *
         * @pipeType - internally change focus state
         */

        private handleBlur() {
            this.focused = false;
        }
    }

</script>

<style lang="scss" scoped>

    .v-input-wrap {

        .v-input-label {
            color: $front-main;
            font-weight: 700;
            font-size: 1rem;
            background-color: $front-main;
            color: $back-main;
            padding: .4rem 1rem .4rem 1rem;
            margin-bottom: .2rem;
            display: table;
            border-radius: 5px;
            transition: color .3s;

            &.focused {
                background: #12c2e9;
                background: -webkit-linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
                background: linear-gradient(to right, #f64f59, #c471ed, #12c2e9);
                color: white;
            }
        }

        input[type="text"] {
            background: transparent;
            border: 3px solid $front-main;
            border-bottom-left-radius: 5px;
            border-radius: 5px;
            padding: 8px;
            font-weight: bold;
            color: $front-main;
            width: 250px;
            
            &::-webkit-input-placeholder {
                color: $front-main;
                font-style: oblique;
                font-size: .7rem;
                font-weight: 100;
            }
        }
    }

</style>