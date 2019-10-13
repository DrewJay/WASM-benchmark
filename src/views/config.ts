// Configuration file describing data for generating
// DOM content for benchmark and functional data like
// callback names or identifiers.

const benchmarkConfig: object[] = [
    {
        id: 'prime_lookup',
        label: 'Prime Lookup',
        note: 'Finds the amount of prime numbers in given range.',
        fields: [
            {
                name: 'range',
                type: 'text',
                label: 'Number Range',
                placeholder: '@int',
            },
        ],
    },
    {
        id: 'taylor_chain',
        label: 'Taylor Chain',
        note: 'Calulates power using taylor logarithm method. Accuracy increases amount of iterations.',
        fields: [
            {
                name: 'base',
                type: 'text',
                label: 'Power Base',
                placeholder: '@double',
            },
            {
                name: 'exponent',
                type: 'text',
                label: 'Power Exponent',
                placeholder: '@int',
            },
            {
                name: 'accuracy',
                type: 'text',
                label: 'Accuracy',
                placeholder: '@int',
            },
        ],
    },
    {
        id: 'iterative_allocation',
        label: 'Iterative Allocation',
        note: 'Creates n data structures including one randomly generated letter and one integer.',
        fields: [
            {
                name: 'iterations',
                type: 'text',
                label: 'Number of Iterations',
                placeholder: '@int',
            },
        ],
    },
    {
        id: 'noperf_selfexec_info',
        label: 'Session information',
        norun: true,
        fields: [
            {
                name: 'info',
                type: null,
            },
        ],
    },
];

const aliasConfig: object = {
    js: {
        prime_lookup: 'checkPrimes',
        taylor_chain: 'taylorPow',
        iterative_allocation: 'iterativeAllocator',
        noperf_selfexec_info: 'setInfo',
    },
    c: {
        prime_lookup: '_check_primes',
        taylor_chain: '_taylor_pow',
        iterative_allocation: '_iterative_allocator',
    },
};

export {
    benchmarkConfig,
    aliasConfig,
};
