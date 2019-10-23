#include "headers/evts.h"

/**
 * Mousemove event callback function handler.
 * 
 * @param {int} eventType - flag defining event type 
 * @param {EmscriptenMouseEvent*} e - event object
 * @param {void*} userData - callback parameter 
 * 
 * @return {EM_BOOL} - status code
 */
EM_BOOL mouse_callback(int eventType, const EmscriptenMouseEvent *e, void *userData) {
    
    if (eventType == EMSCRIPTEN_EVENT_MOUSEMOVE) {
        mouseX = e->targetX;
        mouseY = e->targetY;
    }

    if(eventType == EMSCRIPTEN_EVENT_MOUSELEAVE) {
        mouseX = -1;
    }

    return 0;
}

/**
 * Setup event handlers by calling emscripten
 * callback functions. This syntax is correct,
 * since it is from official documentation.
 * 
 * @return {void}
 */
void evts_setup() {    
    EMSCRIPTEN_RESULT ret = emscripten_set_mousemove_callback("screen", 0, 1, mouse_callback);
    ret = emscripten_set_mouseleave_callback("screen", 0, 1, mouse_callback);
}