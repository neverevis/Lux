#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/gl_renderer.h>
#include <core/log.h>

#include <EGL/egl.h>

using gl = Lux::GLRenderer;

PFNGLCLEARPROC          gl::Clear = nullptr;
PFNGLCLEARCOLORPROC     gl::ClearColor = nullptr;

void* Lux::GLRenderer::load_fn(const char* fn_name){
    void* fn = (void*) eglGetProcAddress(fn_name);

    if(fn){
        return fn;
    }

    LUX_ERROR("failed to load {} function pointer", fn_name);

    return nullptr;
}

#endif