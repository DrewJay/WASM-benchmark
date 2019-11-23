import { EndpointCollection } from '@/types/networkTypes';

/**
 * Collection of API endpoints used in project.
 */
export const endpointCollection: EndpointCollection = {
    setWasmb: {
        url: 'https://jsonstream.herokuapp.com/api/set',
        method: 'POST',
    },
    getWasmb: {
        url: 'https://jsonstream.herokuapp.com/api/get',
        method: 'POST',
    },
};
