#ifndef _AOWF 

#define _AOWF

#include <stdlib.h>
#include <emscripten.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int i;
    char c;
} stackItem;

typedef struct {
    int size;
    stackItem **data;
} stack;

stack *iterative_allocator (int amount);
int get_heap_offset ();
int get_size_factor (); 

#endif