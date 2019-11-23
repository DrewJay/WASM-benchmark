module.exports = {
    css: {
        loaderOptions: {
            sass: {
                prependData: `@import "@/assets/styles/colors.scss";
                              @import "@/assets/styles/variables.scss";`
            },
        }
    },
    pwa: {
        iconPaths: {
           favicon32: 'img/icons/logo.png',
        }
    },
}