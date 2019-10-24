#ifndef _CANVAS

#define _CANVAS

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <emscripten.h>
#include "config.h"

typedef struct {
    double x;
    double y;
    double horizontal_coe;
    double vertical_coe;
    int horizontal_way;
    int vertical_way;
} point;

typedef struct {
    int item_amount;
    int item_size;
    point *dataPtr;
} pointLine;

pointLine *point_l;
int width;
int height;
int mouseX;
int mouseY;

double randouble        (double min, double max);
pointLine *canvas_init  (int c_width, int c_height, int amount);
pointLine *canvas_move  ();
int charge              (double num);

#endif