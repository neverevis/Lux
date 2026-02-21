#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

#include <platform/native.hpp>
#include <platform/graphics_context.hpp>
#include <platform/window.hpp>

#include <graphics/gl.hpp>

#include <core/debug.hpp>

#include <EGL/eglplatform.h>
#include <EGL/egl.h>

Lux::Platform::GraphicsContext::GraphicsContext(const System& system)
    : system_(system)
    , native(native_)
    , surface_settings(surface_settings_)
{
    native_.egl_display = eglGetDisplay((EGLNativeDisplayType) system.native.display);
    LUX_VERIFY(native.egl_display, "failed to load egl display");
    
    LUX_VERIFY(eglInitialize(native.egl_display, nullptr, nullptr), "failed to initialize egl");

    EGLint egl_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLint num_configs;
    eglChooseConfig(native.egl_display , egl_attribs, &native_.egl_config, 1, &num_configs);

    EGLint id;
    eglGetConfigAttrib(native.egl_display, native.egl_config, EGL_NATIVE_VISUAL_ID, &id);

    surface_settings_.visual_id = (unsigned long) id;
}

Lux::Platform::GraphicsContext::~GraphicsContext(){
    //TODO
}

bool Lux::Platform::GraphicsContext::create(const Window& window){
    window_ = &window;
    native_.egl_surface = eglCreateWindowSurface(native.egl_display, native.egl_config, (EGLNativeWindowType) window.native.window, nullptr);

    LUX_VERIFY(native.egl_surface, "failed to create window surface");

    LUX_VERIFY(eglBindAPI(EGL_OPENGL_API), "failed to bind OpenGL API");

    int version[8][2] = {{4,6},{4,5},{4,4},{4,3},{4,2},{4,1},{4,0},{3,3}};
    int i = 0;

    bool done = false;
    bool success = false;

    while(!done){
        const EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, version[i][0],
        EGL_CONTEXT_MINOR_VERSION, version[i][1],
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
        };

        native_.egl_context = eglCreateContext(native.egl_display, native.egl_config, EGL_NO_CONTEXT, context_attribs);

        if(native_.egl_context){
            LUX_INFO("OpenGL Core {}.{}",version[i][0],version[i][1]);
            done = true;
            success = true;
        }else if(i < 7){
            i++;
        }else{
            LUX_INFO("Failed to load GL Context");
            done = true;
        }
    }

    if(!success){
        return false;
    }

    Lux::Graphics::gl::init();

    return true;
}

void Lux::Platform::GraphicsContext::swap_buffers(){
    eglSwapBuffers(native.egl_display, native.egl_surface);
}

void Lux::Platform::GraphicsContext::make_current(){
    eglMakeCurrent(native.egl_display, native.egl_surface, native.egl_surface, native.egl_context);
    if(!Graphics::gl::loaded)
        Graphics::gl::init(get_fn_address);
}

void* Lux::Platform::GraphicsContext::get_fn_address(const char* fn_name){
    void* fn = (void*) eglGetProcAddress(fn_name);
    LUX_ASSERT(fn, "failed to load {}", fn_name);
    return fn;
}

#endif