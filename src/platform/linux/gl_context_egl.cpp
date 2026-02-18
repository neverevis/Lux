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
};

Lux::GLContext::GLContext(Lux::Window& window){
    X11Handle* h = (X11Handle*) window.get_native_handle();
    m_display = eglGetDisplay((EGLNativeDisplayType) h->display);

    eglInitialize(m_display , nullptr, nullptr);

    const int egl_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_RED_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLConfig egl_config;
    EGLint num_config;
    
    eglChooseConfig(m_display, egl_attribs, &egl_config, 1, &num_config);

    m_window = eglCreateWindowSurface(m_display, egl_config, (EGLNativeWindowType) h->window, nullptr);

    const EGLint context_attribs[] = {
        EGL_CONTEXT_MAJOR_VERSION, 4,
        EGL_CONTEXT_MINOR_VERSION, 6,
        EGL_NONE
    };

    m_context = (void*) eglCreateContext(m_display, egl_config, nullptr, context_attribs);
}

Lux::GLContext::~GLContext(){
    
}

void Lux::GLContext::make_current(){
    eglMakeCurrent(m_display, m_window, m_window, m_context);
}

#endif