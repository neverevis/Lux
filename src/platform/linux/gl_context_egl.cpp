#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/gl_context.h>
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

Lux::GLContext::GLContext(Lux::Window& window){
    X11Handle* h = (X11Handle*) window.get_native_handle();

    m_display = h->egl_display;
    
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
}

Lux::GLContext::~GLContext(){
    
}

void Lux::GLContext::swap_buffers(){
    eglSwapBuffers(m_display, m_window);
}

void Lux::GLContext::make_current(){
    eglMakeCurrent(m_display, m_window, m_window, m_context);
}

#endif