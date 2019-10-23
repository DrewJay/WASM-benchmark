#ifndef _AOWF 

#define _AOWF

#include <stdlib.h>
#include <emscripten.h>
#include <time.h>
#include <stdio.h>

typedef struct {
    int i;
    char c;
} pack;

typedef struct {
    int item_amount;
    int item_size;
    pack *dataPtr;
} packLine;

packLine *pack_l;

packLine *iterative_allocator (int amount);
int get_heap_offset ();
int get_size_factor (); 

#endif