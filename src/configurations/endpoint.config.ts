import { EndpointCollection } from '@/structures/types.struct';

/**
 * Collection of API endpoints used in project.
 */
export const endpointCollection: EndpointCollection = {
    setWasmb: {
        name: 'setWasmb',
        url: 'https://jsonstream.herokuapp.com/api/set',
        method: 'POST',
    },
    getWasmb: {
        name: 'getWasmb',
        url: 'https://jsonstream.herokuapp.com/api/get',
        method: 'POST',
    },
};
