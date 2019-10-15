#include "headers/prime.h"

/** 
 * Check if number is prime by iterating 
 * over all previous numbers and performing
 * cross division.
 * 
 * @param {int} num - the number we are checking
 * 
 * @return {int} - flag if number is prime
 */

int is_prime(int num) {
    for(int i=2; i<num; i++) {
        if(num%i == 0) return 0;
    }
    return (num != 1 && num != 0) ? 1 : 0;
}


/** 
 * Simply iterate over $num numbers and
 * apply prime check on them. Count and
 * return the amount of primes.
 * 
 * @param {int} num - first n whole numbers
 * 
 * @return {int} - the amount of primes
 */

int check_primes(num) {
    int count = 0;
    for(int i=0; i<num; i++) {
        if (is_prime(i)) count++;
    }
    return count;
}


/** 
 * Pass numeric range constant from C
 * to JavaScript global scope.
 * 
 * @return {int} - number range
 * 
 */

int get_numeric_range() {
    return NUM_RANGE;
}