import Vue from 'vue';
import Router from 'vue-router';
import Main from '@/views/main.view.vue';

Vue.use(Router);

export default new Router({
    routes: [{
        path: '/',
        name: 'main',
        component: Main,
    } ],
});
