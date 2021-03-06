#include "headers/canvas.h"

/**
 * Initialize canvas points. Returns address of pointLine,
 * object storing metadata and address of actual points
 * ordered in linear fashion.
 * 
 * @param c_width Width of canvas
 * @param c_height Height of canvas
 * @param amount Amount of points to initialize
 * @return Address of pointLine object
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
    
    for (int i = 0; i < point_l->item_amount; i++) {
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
 * @return Address of pointLine object
 */
pointLine *canvas_move() {
    for (int i = 0; i < point_l->item_amount; i++) {
        int boost = 0;

        if ((mouseX > 0) 
            && ((point_l->dataPtr[i].x < mouseX + BOOST_RADIUS && point_l->dataPtr[i].x > mouseX - BOOST_RADIUS)
            && (point_l->dataPtr[i].y < mouseY + BOOST_RADIUS && point_l->dataPtr[i].y > mouseY - BOOST_RADIUS))
        ) {
            boost = BOOST;
        }

        double effective_boostX = charge(point_l->dataPtr[i].horizontal_coe) * boost;
        double effective_boostY = charge(point_l->dataPtr[i].vertical_coe) * boost;

        double posX = point_l->dataPtr[i].x + point_l->dataPtr[i].horizontal_coe + effective_boostX;
        double posY = point_l->dataPtr[i].y + point_l->dataPtr[i].vertical_coe + effective_boostY;

        if (posX <= 0 || posX >= width) {
            point_l->dataPtr[i].horizontal_coe *= -1;
        }

        if (posY <= 0 || posY >= height) {
            point_l->dataPtr[i].vertical_coe *= -1;
        }

        point_l->dataPtr[i].x = posX;
        point_l->dataPtr[i].y = posY;
    }

    return point_l;
}

/**
 * Generate random double in range.
 * 
 * @param min Lower bound
 * @param max Upper bound
 * @return Random double
 */
double randouble(double min, double max) {
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

/**
 * Find if number is positive or negative. Return charge
 * index (1 or -1) representing this infomation.
 * 
 * @param num Number
 * @return Charge index
 */
int charge(double num) {
    return (num >= 0) ? 1 : -1;
}

/**
 * Main routine shared accross all modules.
 */
int main() {
    srand(time(NULL));
}