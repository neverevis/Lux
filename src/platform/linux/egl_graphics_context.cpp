#include <platform/detect.h>
#ifdef PLATFORM_LINUX

#include <platform/handles.h>
#include <platform/graphics_context.h>
#include <platform/window.h>
#include <core/debug.h>

#include <EGL/eglplatform.h>
#include <EGL/egl.h>

Lux::Platform::GraphicsContext::GraphicsContext(const System& system)
    : m_system(system)
{
    m_context_handle.egl_display = eglGetDisplay((EGLNativeDisplayType) system.get_native_handle().display);
    LUX_VERIFY(m_context_handle.egl_display , "failed to load egl display");
    
    LUX_VERIFY(eglInitialize(m_context_handle.egl_display  , nullptr, nullptr), "failed to initialize egl");

    EGLint egl_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLint num_configs;
    eglChooseConfig(m_context_handle.egl_display , egl_attribs, &m_context_handle.egl_config, 1, &num_configs);
}

Lux::Platform::GraphicsContext::~GraphicsContext(){
    
}

const Lux::Platform::GraphicsRequirements Lux::Platform::GraphicsContext::query_requirements(){
    EGLint id;
    eglGetConfigAttrib(m_context_handle.egl_display, m_context_handle.egl_config, EGL_NATIVE_VISUAL_ID, &id);
    
    GraphicsRequirements gr;
    gr.visual_id = (unsigned long) id;

    return gr;
}

bool Lux::Platform::GraphicsContext::create(const Window& window){
    m_window = &window;
    m_context_handle.egl_surface = eglCreateWindowSurface(m_context_handle.egl_display, m_context_handle.egl_config, (EGLNativeWindowType) m_window->get_native_handle().window, nullptr);

    LUX_VERIFY(m_context_handle.egl_surface, "failed to create window surface");

    const EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 6,
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
    };

    LUX_VERIFY(eglBindAPI(EGL_OPENGL_API), "failed to bind OpenGL API");

    m_context_handle.egl_context = eglCreateContext(m_context_handle.egl_display, m_context_handle.egl_config, EGL_NO_CONTEXT, context_attribs);

    LUX_VERIFY(m_context_handle.egl_context, "failed to create egl context");

    if(!m_context_handle.egl_context){
        return false;
    }

    return true;
}

void Lux::Platform::GraphicsContext::swap_buffers(){
    eglSwapBuffers(m_context_handle.egl_display, m_context_handle.egl_surface);
}

void Lux::Platform::GraphicsContext::make_current(){
    eglMakeCurrent(m_context_handle.egl_display, m_context_handle.egl_surface, m_context_handle.egl_surface, m_context_handle.egl_context);
}

#endif