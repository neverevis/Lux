#include <platform/detect.hpp>
#ifdef PLATFORM_WINDOWS

#include <platform/gl_loader.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

void* Lux::Platform::load_gl_function(const char *fn_name){
    void* fn = (void*) wglGetProcAddress(fn_name);
    
    if(fn)
        return fn;

    HMODULE opengl32 = LoadLibraryA("opengl32.dll");

    if(!opengl32)
        return nullptr;

    fn = (void*) GetProcAddress(opengl32, fn_name);

    return fn;
}

#endif