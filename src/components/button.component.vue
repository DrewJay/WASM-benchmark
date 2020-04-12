<template>
    <div class="v-button">
        
        <div class="v-button-wrap" :class="flags">
            
            <input 
                type="button"
                @click="emitValue"
                :value="label"
            >
            
        </div>

    </div>
</template>

<script lang="ts">
import {
    Component,
    Prop,
    Vue,
    Emit,
} from 'vue-property-decorator';
import { Emitor } from '@/structures/types.struct';

@Component
export default class VButton extends Vue implements Emitor {
    @Prop() private label!: string;
    @Prop() private name!: string;
    @Prop() private flags!: string[];

    /**
     * Emit value when button is pressed.
     *
     * @param evt - Event object reference
     * @returns Name of button
     */
    @Emit('press')
    public emitValue(evt: any) {
        return this.name;
    }
}
</script>

<style lang="scss" scoped>
.v-button-wrap {

    input[type="button"] {
        font-size: $button-font-size;
        border: 2px solid $wasm-front;
        color: #d4d0fb;
        padding: .8em 1.5em;
        font-weight: bold;
        border-radius: 5px;
        background-color: $wasm-back;
        transition: background-color .3s, color .3s;
        box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23);
        cursor: pointer;
        width: 272px;

        &:hover {
            background-color: $front-main;
            color: $back-main;
        }
    }

    &.generic {
        input[type="button"] {
            box-shadow: none;
            font-size: $button-generic-font-size;
            width: 250px;
            padding: .5em 1.5em;
        }
    }
}
</style>