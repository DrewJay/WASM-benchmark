#include "headers/config.h"
#include "headers/aowf.h"

/** 
 * Create ${amount} amount of structures and
 * allocate sufficient memory for them.
 * 
 * Returns addres 's' of the stack.
 * 
 * val(s) = | sz | sz | sz | sz | dt | dt | dt | dt |
 * where sz = int(sz), dt = int(addr(dt))
 * 
 * val(dt) = | it | it | it | it | ...*amount
 * where it = int(addr(it))
 * 
 * val(it) = si
 * where si = struct(stackItem)
 * 
 * @param {int} amount - amount of items to define
 * 
 * @return {stack*} - address of a stack
 */

stack *iterative_allocator(int amount) {

    srand(time(NULL));

    stack* _stack = malloc(sizeof(stack*));
    _stack->data = malloc(sizeof(stackItem*) * amount);
    _stack->size = amount;

    for(int itr=0; itr<_stack->size; itr++) {
    
        stackItem item;
        item.i = itr;
        item.c = 'A' + (random() % 26);

        _stack->data[itr] = item;
    }

    return _stack;
}


/**
 * Find where malloc allocates dummy data. Useful
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
    return sizeof(stackItem);
}