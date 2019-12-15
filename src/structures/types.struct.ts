import API from '@/modules/api.module';

/**
 * Component that emits value.
 */
export interface Emitor {
    emitValue: (evt: any) => {};
}

/**
 * General data structure of data transferred during API communication.
 */
export type compositeDataCarry = object | any[] | null;

/**
 * Set of available HTTP methods.
 */
export type HTTPMethod = 'GET' | 'PUT' | 'POST' | 'DELETE';

/**
 * HTTP endpoint definition.
 */
export interface Endpoint {
    name: string;
    url: string;
    method: HTTPMethod;
}

/**
 * Collection of HTTP endpoints.
 */
export interface EndpointCollection {
    [key: string]: Endpoint;
}

/**
 * Component making HTTP requests.
 */
export interface APIConsumer {
    postman: API;
}
