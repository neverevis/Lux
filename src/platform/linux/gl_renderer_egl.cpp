#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/gl_renderer.h>
#include <core/log.h>

#include <EGL/egl.h>
#include <core/debug.h>

using gl = Lux::GLRenderer;

PFNGLCLEARPROC          gl::Clear = nullptr;
PFNGLCLEARCOLORPROC     gl::ClearColor = nullptr;

bool Lux::GLRenderer::init(){
    if(eglGetCurrentContext()){
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
    void* fn = (void*) eglGetProcAddress(fn_name);

    if(fn){
        return fn;
    }

    LUX_ERROR("failed to load {} function pointer", fn_name);

    return nullptr;
}

#endif