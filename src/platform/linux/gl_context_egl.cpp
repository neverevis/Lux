#include "platform/window.h"
#include <EGL/eglplatform.h>
#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/gl_context.h>

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

    const EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 6,
        EGL_NONE
    };

    m_context = (void*) eglCreateContext(m_display, h->egl_config, nullptr, context_attribs);
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