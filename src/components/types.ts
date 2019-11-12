import { API } from '@/modules/network/api';

/**
 * Component that emits value.
 */
export interface Emitor {
    emitValue: (evt: any) => {};
}

/**
 * Component making HTTP requests.
 */
export interface APIConsumer {
    httpCaller: API;
}
