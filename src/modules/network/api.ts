import { Endpoint, compositeDataCarry } from '@/types/networkTypes';
import { endpointCollection } from '@/modules/network/endpoints';
import axios from 'axios';


/**
 * This class is used for sending HTTP requests to my public API.
 */
export class API {

    private name!: string;
    private data!: compositeDataCarry;

    /**
     * Create instance of API component.
     *
     * @param name - Name of component using this instance
     */
    constructor(name: string) {
        this.name = name;
    }

    /**
     * Load the data to the instance internal state.
     *
     * @param data - Data object we want to send
     * @returns Reference to itself
     */
    public feed(data: compositeDataCarry): API {
        this.data = data;
        return this;
    }

    /**
     * Make HTTP request to named endpoint.
     *
     * @param name - The name of the endpoint
     * @returns Request data
     */
    public async request(name: string, stringify: boolean = false): Promise<any> {
        const data = (stringify) ? JSON.stringify(this.data) : this.data;

        const config: Endpoint = this.lookup(name);
        try {
            const response: any = await axios({
                url: config.url,
                method: config.method,
                data,
            });

            return response;

        } catch (HTTPException) {
            return false;
        }
    }

    /**
     * Find endpoint by name and return it.
     *
     * @param name - The name of the endpoint
     * @returns - Endpoint configuration object
     */
    private lookup(name: string): Endpoint {
        return endpointCollection[name];
    }
}
