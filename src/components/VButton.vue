<template>
    <div class="v-button">
        
        <div class="v-button-wrap">
            
            <input 
                type="button"
                @click="handlePress"
                :value="label"
            >
            
        </div>

    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';

    @Component
    export default class VButton extends Vue {

        @Prop() private label!: string;
        @Prop() private name!: string;


        /**
         * Emit value when button is pressed.
         *
         * @param {any} evt - event object reference
         *
         * @return {string} - name of button
         */

        @Emit('press')
        private handlePress(evt: any) {
            return this.name;
        }
    }

</script>

<style lang="scss" scoped>

    .v-button-wrap {

        input[type="button"] {
            border: 2px solid $front-main;
            color: $front-main;
            padding: .8em 1.5em;
            font-weight: bold;
            border-radius: 5px;
            background-color: $back-main;
            transition: background-color .3s, color .3s;
            cursor: pointer;
            width: 272px;

            &:hover {
                background-color: $front-main;
                color: $back-main;
            }
        }
    }

</style>