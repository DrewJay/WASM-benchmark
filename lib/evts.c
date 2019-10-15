#include "headers/evts.h"

/**
 * Click event callback function handler.
 * 
 * @param {int} eventType - flag defining event type 
 * @param {EmscriptenMouseEvent*} e - event object
 * @param {void*} userData - callback parameter 
 * 
 * @return {EM_BOOL} - status code
 */

EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
    
    if (eventType == EMSCRIPTEN_EVENT_CLICK) {/*...*/};

    return 0;
}


int main() {    
    EMSCRIPTEN_RESULT ret = emscripten_set_click_callback(0, 0, 1, mouse_callback);
    return 0;
}