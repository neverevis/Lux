#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

#include <platform/gl_loader.hpp>
#include <EGL/egl.h>


void* Lux::Platform::load_gl_function(const char* fn_name){
    void* fn = (void*) eglGetProcAddress(fn_name);
    return fn;
}

#endif