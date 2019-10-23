#include "headers/config.h"
#include "headers/aowf.h"

/** 
 * Create ${amount} amount of structures and
 * allocate sufficient memory for them. This
 * is performance benchmark method and member
 * variables of pack structure have no purpose.
 * 
 * @param {int} amount - amount of items to create
 * 
 * @return {packLine*} - address of the packLine
 */
packLine *iterative_allocator(int amount) {

    free(pack_l->dataPtr);
    free(pack_l);

    pack_l = malloc(sizeof *pack_l);
    pack_l->item_amount = amount;
    pack_l->item_size = sizeof(pack);
    pack_l->dataPtr = malloc(sizeof *pack_l->dataPtr * amount);

    for(int itr=0; itr<pack_l->item_amount; itr++) {
    
        pack item;
        item.i = itr;
        item.c = 'A' + (random() % 26);

        pack_l->dataPtr[itr] = item;
    }

    return pack_l;
}

/**
 * Find where malloc allocates dummy dataPtr. Useful
 * when deciding real usable memory.
 * 
 * @return {int} - memory address
 */
int get_heap_offset() {
    void *item = malloc(sizeof(char));
    free(item);
    return (int)item;
}

/**
 * This much memory is taken per one iteration.
 * 
 * @return {int} - amount of bytes
 */
int get_size_factor() {
    return sizeof(pack);
}