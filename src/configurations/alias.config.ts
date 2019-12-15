/**
 * Configuration used to describe dynamic callbacks
 * during performance measurements.
 */
export default {
    js: {
        prime_lookup: 'checkPrimes',
        taylor_chain: 'taylorPow',
        memconsume_iterative_allocation: 'iterativeAllocator',
        selfexec_info: 'setInfo',
        memconsume_noperf_particle_animation: 'setCanvas',
    },
    c: {
        prime_lookup: '_check_primes',
        taylor_chain: '_taylor_pow',
        memconsume_iterative_allocation: '_iterative_allocator',
    },
};
