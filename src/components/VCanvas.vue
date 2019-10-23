<template>
    <div class="v-canvas">
        <canvas :width="width" :height="height" :id="id"></canvas>
    </div>
</template>

<script lang="ts">
    
    import { Component, Prop, Vue, Emit } from 'vue-property-decorator';

    @Component
    export default class VCanvas extends Vue {

        @Prop() private id!: string;
        @Prop() private width!: string[];
        @Prop() private height!: string;

        // When canvas is loaded, apply WASM event handlers.
        private mounted() {
            (this as any).module._evts_setup();
        }
    }

</script>

<style lang="scss" scoped>

    canvas {
        background-color: black;
        border: 2px solid $front-main;
    }

</style>