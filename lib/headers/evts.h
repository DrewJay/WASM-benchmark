#ifndef _EVTS

#define _EVTS

#include <emscripten.h>
#include <emscripten/html5.h>

EM_BOOL mouse_callback (int, const EmscriptenMouseEvent*, void*);

#endif