<template>
    <div id="app">
        <router-view/>
    </div>
</template>

<script lang="ts">
    
    import { Component, Vue } from 'vue-property-decorator';

    @Component
    export default class App extends Vue {

        /**
         * Main lifecycle hook.
         */
        private mounted() {
            setTimeout(() => {
                const elem: any = document.getElementById('logo');
                elem.classList.add('move');
            }, 1000);
        }
    }

</script>

<style lang="scss">

    html {
        width: 100%;
    }

    body {
        padding-left: 10px;
        padding-right: 10px;
        width: calc(100% - 20px);
        display: inline-block;
    }

    $size: 300px;

    html, body {
        background-color: $back-main;
        height: 100%;
        margin: 0;

        #logo {
            width: $size;
            opacity: 0;
            height: $size;
            position: absolute;
            left: 50%;
            transform: translate(-50%, -50%);
            top: 50%;
            transform-origin: top;
            transition: opacity .3s, width .3s, height .3s, top .3s, left .3s;

            &.move {
                top: 0;
                left: calc(100% - #{$size/2} - #{$size/4});
                transform: scale(.5);
            }
        }
    }

    #app, body > #logo {
        font-family: 'Quattrocento Sans', sans-serif;
    }

</style>
