import { API } from '@/modules/network/api';

/**
 * Autoinitialize members of a class by keys specified.
 *
 * @param keys - Array of keys specifying the type of class annotated
 * @returns - Modified constructor
 */
export const AutoInit: (keys?: string[]) => any = (keys?: string[]): any => {
    return (constructor: () => {}): any => {

        keys = keys || ['APIConsumer'];

        if (keys.includes('APIConsumer')) {
            constructor.prototype.httpCaller = new API(constructor.name);
        }
        return constructor;
    };
};
