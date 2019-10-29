module.exports = {
    css: {
        loaderOptions: {
            sass: {
                prependData:  `@import "@/assets/styles/colors.scss";`
            },
        }
    }
}