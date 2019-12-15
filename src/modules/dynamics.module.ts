import { compositeDataCarry } from '@/structures/types.struct';

/**
 * Class containing dynamic callbacks that can be invoked on specific context.
 * @beta
 */
export default class Dynamics {

    /**
     * Execute local function over specific context.
     *
     * @param context - Dynamic context
     * @param callback - Name of function to execute
     */
    public static invoke(context: any, callback: string) {
        (Dynamics as any)[callback].apply(context);
    }

    /**
     * This dynamic callback resets stateful public API to empty array shape.
     */
    private static async apiReset() {
        const dContext: any = this;

        const updated: compositeDataCarry = {key: 'wasmb', value: JSON.stringify([])};
        await dContext.postman.feed(updated).request('setWasmb');
    }

    /**
     * This callback is dynamically called by invokeSelfExecutables
     * function and fills fallback div container with proper HTML.
     */
    private static setInfo() {

        const dContext: any = (this as any);

        const length: any = dContext.module.HEAP8.length;
        const stackOffset: any = (window as any).STACK_BASE;
        const heapOffset: any = (window as any).STACK_MAX;

        dContext.generated =
            `<div><span>Total memory</span> <span>${length} bytes</span></div>
             <div><span>STACK offset</span> <span>${stackOffset}th byte</span></div>
             <div><span>HEAP offset</span> <span>${heapOffset}th byte</span></div>
             <div><span>Alloc index</span> <span>~${(length - stackOffset) / dContext.module._get_size_factor()} itrs</span></div>`;
        }
}
