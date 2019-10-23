#include "headers/pow.h"

/*
 * Function:  taylor_log
 * --------------------
 * Estimates logarithm value using Taylor polynomial method. Two methods are used, decided by interval of input number.
 * It is expected to return relatively accurate logarithm approximation. Accuracy of estimation should grow with
 * increased amount of iterations.
 *
 * For interval (0;1) is used formula: log(1-x) = -x-(x^2/2)-(x^3/3)-...-(x^n/n)
 * For interval <1;INF) is used formula: log(x) = SUM[ ((x-1)/x)^n/n ]
 *
 * @param {double} x - subject of logarithm
 * @param {double} n - amount of iterations
 *
 * @return {double} - approximation of logarithm value
 */
double taylor_log(double x, unsigned int n) {
 
    double ref = 1-x;
    double approx = 0.0;
    double pw = 1.0;
 
    for(unsigned int i=0; i<=n-1; i++) {
        
        if(x > 0 && x < 1) {
            pw = pw*ref;
            approx = approx - (pw/(i+1));
        }
 
        else {
            pw = pw*((x-1)/x);
            approx = approx + pw/(i+1);
        }
    }
 
    return approx;
}

/*
 * Function:  taylor_pow
 * --------------------
 * Estimates power value using function taylor_log(). It is expected to return relatively accurate power approximation.
 * Amount of iterations affects not only power calculation, but logarithm too.
 *
 * @param {double} x - power base
 * @param {double} y - power exponent
 * @param {int} n - amount of iterations
 *
 * @return {double} - approximation of value of power function
 */
double taylor_pow(double x, double y, unsigned int n) {
    
    double approx = 1.0;
    double frac = 1.0;
 
    for(unsigned int i=0; i<=n-1; i++) {
        frac = frac*(((y*taylor_log(x,n))/(i+1)));
        approx = approx + frac;
    }
 
    return approx;
}

/*
 * Pass numeric range constant from C
 * to JavaScript global scope.
 * 
 * @return {exponentialDefaults*} - structure with defaults information
 */
exponentialDefaults *get_exponential_defaults() {
  
    exponentialDefaults *ed = malloc(sizeof(exponentialDefaults));
    ed->base = BASE;
    ed->exponent = EXPO;
    ed->iterations = ITER;

    return ed;
}