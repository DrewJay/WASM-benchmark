import Vue, { VNode } from 'vue';

declare global {
    namespace JSX {
        interface IntrinsicElements {
            [elem: string]: any;
        }
    }
}
