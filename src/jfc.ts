// JS implementations of C functions.
// Used to measure performance deltas.

/**
 * Checks if number is prime in efficient fashion.
 *
 * @param num - number to check
 *
 * @returns prime status
 */
const isPrime = (num: number) => {
    for (let i = 2; i < num; i++) {
        if (num % i === 0) { return 0; }
    }
    return (num !== 1 && num !== 0) ? 1 : 0;
};

/**
 * Searches first @num numbers for primes.
 *
 * @param num - numeric range
 *
 * @returns amount of prime numbers
 */
const checkPrimes = (num: number) => {
    let count: number = 0;
    for (let i = 0; i < num; i++) {
        if (isPrime(i)) { count++; }
    }
    return count;
};

/**
 * Calculate Taylor logarithm.
 *
 * @param x - logarithm subject
 * @param n - amount of iterations
 *
 * @returns logarithm approximation
 */
const taylorLog = (x: number, n: number) => {

    const ref: number = 1 - x;
    let approx: number = 0.0;
    let pw: number = 1.0;

    for (let i = 0; i <= n - 1; i++) {

        if (x > 0 && x < 1) {
            pw = pw * ref;
            approx = approx - (pw / (i + 1));
        } else {
            pw = pw * ((x - 1) / x);
            approx = approx + pw / (i + 1);
        }
    }
    return approx;
};

/**
 * Use Taylor logarithm to calculate power.
 *
 * @param x - power base
 * @param y - power exponent
 * @param n - amount of iterations.
 *
 * @returns power approximation
 */
const taylorPow = (x: number, y: number, n: number) => {

    let approx: number = 1.0;
    let frac: number = 1.0;

    for (let i = 0; i <= n - 1; i++) {
        frac = frac * (((y * taylorLog(x, n)) / (i + 1)));
        approx = approx + frac;
    }
    return approx;
 };

/**
 * Iteratively create @amount structures.
 *
 * @param amount - the number of structures
 *
 * @returns allocated structures
 */
const iterativeAllocator = (amount: number): object => {

    const arr = new Array(amount);

    for (let i = 0; i < amount; i++) {
        const obj = {
            i,
            c: String.fromCharCode(Math.floor(Math.random() * 26) + 97),
        };
        arr.push(obj);
    }

    const struct: object = {
        size: amount,
        data: arr,
    };

    return struct;
};

export default {
    checkPrimes,
    taylorPow,
    iterativeAllocator,
};
