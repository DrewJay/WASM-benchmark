#include "headers/canvas.h"

pointLine *point_l;
int width;
int height;

/**
 * Initialize canvas points. Returns address of pointLine,
 * object storing metadata and address of actual points
 * ordered in linear fashion.
 * 
 * @param {int} c_width - width of canvas
 * @param {int} c_height - height of canvas
 * @param {int} amount - amount of points to initialize
 * 
 * @return {pointLine*} - address of pointLine object
 */

pointLine *canvas_init(int c_width, int c_height, int amount) {

    free(point_l->dataPtr);
    free(point_l);

    point_l = malloc(sizeof *point_l);
    point_l->item_amount = amount;
    point_l->item_size = sizeof(point);
    point_l->dataPtr = malloc(sizeof *point_l->dataPtr * amount);

    width = c_width;
    height = c_height;
    
    for(int i=0; i<point_l->item_amount; i++) {
        
        point p;
        p.x = c_width/2;
        p.y = c_height/2;
        p.horizontal_coe = randouble(CNV_COE_MIN, CNV_COE_MAX);
        p.horizontal_way = rand() & 1;
        p.vertical_coe = randouble(CNV_COE_MIN, CNV_COE_MAX);
        p.horizontal_way = rand() & 1;

        point_l->dataPtr[i] = p;
    }

    return point_l;
}


/**
 * Move points of canvas by recalculating their coordinates
 * and coefficients.
 * 
 * @return {pointLine*} - address of pointLine object
 */

pointLine *canvas_move() {
    
    for(int i=0; i<point_l->item_amount; i++) {

        int posX = point_l->dataPtr[i].x + point_l->dataPtr[i].horizontal_coe;
        int posY = point_l->dataPtr[i].y + point_l->dataPtr[i].vertical_coe;

        if(posX <= 0 || posX >= width) {
            point_l->dataPtr[i].horizontal_coe *= -1;
        }

        if(posY <= 0 || posY >= height) {
            point_l->dataPtr[i].vertical_coe *= -1;
        }

        point_l->dataPtr[i].x += point_l->dataPtr[i].horizontal_coe;
        point_l->dataPtr[i].y += point_l->dataPtr[i].vertical_coe;
    }

    return point_l;
}


/**
 * Generate random double in range.
 * 
 * @param {double} min - lower bound
 * @param {double} max - upper bound
 * 
 * @return {double} - random double
 */

double randouble(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}


int main() {
    srand(time(NULL));
}