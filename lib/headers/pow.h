#ifndef _POW

#define _POW

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    int base;
    int exponent;
    int iterations;
} exponentialDefaults;

double taylor_log (double, unsigned int);
double taylor_pow (double, double, unsigned int);
exponentialDefaults *get_exponential_defaults ();

#endif