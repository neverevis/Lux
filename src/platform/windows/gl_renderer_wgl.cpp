#include "core/log.h"
#include <platform/platform.h>
#ifdef PLATFORM_WINDOWS

#include <platform/gl_renderer.h>
#include <core/debug.h>

#include <wingdi.h>
#include <libloaderapi.h>

using gl = Lux::GLRenderer;

PFNGLCLEARPROC          gl::Clear = nullptr;
PFNGLCLEARCOLORPROC     gl::ClearColor = nullptr;

bool Lux::GLRenderer::init(){
    if(!wglGetCurrentContext()){
        LUX_ERROR("failed to init GLRenderer. no context is active");   
        return false; 
    }

    gl::Clear =         (PFNGLCLEARPROC)        load_fn("glClear");
    gl::ClearColor =    (PFNGLCLEARCOLORPROC)   load_fn("glClearColor");

    bool result =
    (bool)gl::Clear & (bool)gl::ClearColor;

    if(!result){
        LUX_ERROR("failed to init GLRenderer");
    }

    return true;
}

void* Lux::GLRenderer::load_fn(const char* fn_name){
    void* fn = (void*) wglGetProcAddress(fn_name);

    if(fn){
        return fn;
    }

    HMODULE opengl32 = LoadLibraryA("opengl32.dll");

    LUX_VERIFY(opengl32, "failed to load opengl32.dll");

    fn = (void*) GetProcAddress(opengl32, fn_name);

    if(fn){
        return fn;
    }

    LUX_ERROR("failed to load {} function pointer", fn_name);

    return nullptr;
}

#endif