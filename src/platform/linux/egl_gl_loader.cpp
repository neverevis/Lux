#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

#include <platform/gl_loader.hpp>
#include <EGL/egl.h>
#include <core/debug.hpp>


void* Lux::Platform::load_gl_function(const char* fn_name){
    void* fn = (void*) eglGetProcAddress(fn_name);
    LUX_ASSERT(fn, "failed to load {}", fn_name);
    return fn;
}

#endif