import API from '@/modules/api.module';

/**
 * Autoinitialize members of a class by keys specified.
 *
 * @param keys - Array of keys specifying the type of class annotated
 * @returns Modified constructor
 */
export const AutoImplement: (keys?: string[]) => any = (keys?: string[]): any => {
    return (constructor: () => {}): any => {

        keys = keys || ['APIConsumer'];

        if (keys.includes('APIConsumer')) {
            constructor.prototype.postman = new API(constructor.name);
        }
        return constructor;
    };
};
