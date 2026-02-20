#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

void* Lux::Platform::load_gl_function(const char* fn_name){
    void* fn = eglGetProcAddress(fn_name);
    return fn;
}

#endif