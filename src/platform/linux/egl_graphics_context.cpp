#include <platform/detect.h>
#ifdef PLATFORM_LINUX

#include <platform/graphics_context.h>
#include <platform/window.h>
#include <core/debug.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <EGL/egl.h>

struct X11Handle{
    Display* display;
    int screen;
    Window window;
    XVisualInfo* visual_info;
    Atom wmDeleteMessage;

    //egl
    EGLDisplay egl_display;
    EGLConfig egl_config;
};

Lux::Platform::GraphicsContext::GraphicsContext(const System& system)
    : m_system(system)
{
    m_context_handle.egl_display = eglGetDisplay((EGLNativeDisplayType) display);
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

    eglGetConfigAttrib(m_context_handle.egl_display, m_context_handle.egl_config, EGL_NATIVE_VISUAL_ID, &gr.visual_id);
}

Lux::Platform::GraphicsContext::~GraphicsContext(){{

}
    
}

bool Lux::Platform::GraphicsContext::create(const Window& window){
    X11Handle* h = (X11Handle*) window.get_native_handle();

    m_window = eglCreateWindowSurface(m_display, h->egl_config, (EGLNativeWindowType) h->window, nullptr);

    LUX_VERIFY(m_window, "failed to create window surface");

    const EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 6,
        EGL_CONTEXT_OPENGL_PROFILE_MASK, EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,
        EGL_NONE
    };

    LUX_VERIFY(eglBindAPI(EGL_OPENGL_API), "failed to bind OpenGL API");

    m_context = (void*) eglCreateContext(m_display, h->egl_config, EGL_NO_CONTEXT, context_attribs);

    LUX_VERIFY(m_context, "failed to create egl context");

    if(!m_context){
        return false;
    }

    return true;
}

void Lux::GLContext::swap_buffers(){
    eglSwapBuffers(m_display, m_window);
}

void Lux::GLContext::make_current(){
    eglMakeCurrent(m_display, m_window, m_window, m_context);
}

#endif