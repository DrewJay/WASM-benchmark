/**
 * Configuration file describing data for generating
 * DOM content for benchmark and functional data like
 * callback names or identifiers.
 */
export default [
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
        note: 'Calulates power using taylor logarithm method.',
        fields: [
            {
                name: '0_base',
                type: 'text',
                label: 'Power Base',
                placeholder: '@double',
            },
            {
                name: '1_exponent',
                type: 'text',
                label: 'Power Exponent',
                placeholder: '@int',
            },
            {
                name: '2_accuracy',
                type: 'text',
                label: 'Accuracy',
                placeholder: '@int',
            },
        ],
    },
    {
        id: 'memconsume_iterative_allocation',
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
        id: 'memconsume_noperf_particle_animation',
        label: 'Particle Animation (Beta)',
        note: 'Compare performance of large amount of partiles being animated.',
        fields: [
            {
                name: 'particles',
                type: 'text',
                label: 'Amount of Particles',
                placeholder: '@int',
            },
            {
                type: 'canvas',
            },
        ],
    },
    {
        id: 'selfexec_info',
        label: 'Session information',
        norun: true,
        fields: [
            {
                type: null,
            },
        ],
    },
    {
        id: 'system_actions',
        label: 'System Actions',
        norun: true,
        fields: [
            {
                name: 'apireset',
                type: 'button',
                label: 'API Reset',
                callback: 'apiReset',
            },
        ],
    },
];
