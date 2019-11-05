<template>
    <div id="app">
        <router-view/>
    </div>
</template>

<style lang="scss">

    html {
        width: 100%;
    }

    body {
        padding: 10px;
        width: calc(100% - 20px);
    }

    html, body {
        background-color: $back-main;
        overflow-y: hidden;
        height: 100%;
        margin: 0;

        #logo {
            $coefficient: calc(7vw - 20px);
            width: $coefficient;
            height: $coefficient;
            position: absolute;
            left: 0;
            right: 0;
            top: 0;
            bottom: 0;
            margin: auto;
            color: #efd469;
            font-size: calc(1rem + #{$coefficient/2});
            border: 5px solid #efd469;
            padding-left: 10px;
            padding-top: 5px;
            vertical-align: middle;
        }
    }

    #app, body > #logo {
        font-family: 'Quattrocento Sans', sans-serif;
    }

</style>
