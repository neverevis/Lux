#include <X11/X.h>
#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/window.h>
#include <core/debug.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
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

Lux::Window::Window(int width, int height, const char* title)
    : m_close_flag(false)
{
    X11Handle* h = new X11Handle{};
    m_native_handle = h;

    XSetWindowAttributes window_attributes = {};

    h->display = XOpenDisplay(nullptr);
    LUX_VERIFY(h->display, "failed to connect to X server");

    h->egl_display = eglGetDisplay((EGLNativeDisplayType) h->display);

    LUX_VERIFY(h->egl_display, "failed to load egl display");

    LUX_VERIFY(eglInitialize(h->egl_display , nullptr, nullptr), "failed to initialize egl");

    EGLint egl_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
        EGL_RED_SIZE, 8, EGL_GREEN_SIZE, 8, EGL_BLUE_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_NONE
    };

    EGLint num_configs;
    eglChooseConfig(h->egl_display, egl_attribs, &h->egl_config, 1, &num_configs);

    EGLint vid;
    eglGetConfigAttrib(h->egl_display, h->egl_config, EGL_NATIVE_VISUAL_ID, &vid);

    XVisualInfo vinfo_template;
    vinfo_template.visualid = vid;
    int n;

    h->visual_info = XGetVisualInfo(h->display, VisualIDMask, &vinfo_template, &n);

    LUX_VERIFY(h->visual_info, "failed to get visual info");

    h->screen = XDefaultScreen(h->display);

    Colormap cmap = XCreateColormap(h->display, XRootWindow(h->display, h->visual_info->screen), h->visual_info->visual, AllocNone);

    LUX_VERIFY(cmap, "failed to create color map");

    XSetWindowAttributes swa = {};
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    swa.background_pixel = XBlackPixel(h->display, h->screen);
    
    h->window = XCreateWindow(h->display, XRootWindow(h->display, h->visual_info->screen), 0, 0, width, height, 0, h->visual_info->depth, InputOutput, h->visual_info->visual, CWColormap | CWEventMask | CWBorderPixel, &swa);

    XStoreName(h->display, h->window, title);

    h->wmDeleteMessage = XInternAtom(h->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(h->display, h->window, &h->wmDeleteMessage, 1);

    m_width = width;
    m_height = height;

    XFlush(h->display);
}

bool Lux::Window::should_close(){
    return m_close_flag;
}

bool Lux::Window::show(){
    if(m_native_handle){
        
        X11Handle* h = (X11Handle*) m_native_handle;
        
        int def_screen = XDefaultScreen(h->display);
        int screen_width = XDisplayWidth(h->display, def_screen);
        int screen_height = XDisplayHeight(h->display, def_screen);
        
        XMapWindow(h->display, h->window);

        int x = screen_width/2 - m_width/2;
        int y = screen_height/2 - m_height/2;

        XMoveWindow(h->display, h->window, x, y);

        XEvent e;
        do {
            XNextEvent(h->display, &e);
        } while (e.type != MapNotify);

        XFlush(h->display);

        return true;
    }

    return false;
}

void* Lux::Window::get_native_handle(){
    if(m_native_handle){
        return m_native_handle;
    }
}

void Lux::Window::poll_events(){
    X11Handle* h = (X11Handle*) m_native_handle;
    
    XEvent event;
    while (XPending(h->display)) {
        XNextEvent(h->display, &event);

        if(event.type == ClientMessage){
            if(event.xclient.data.l[0] == h->wmDeleteMessage){
            m_close_flag = true;
        }
        }
    }
}

bool Lux::Window::close(){
    if(!m_close_flag){
        m_close_flag = true;

        return true;
    }

    return false;
}

Lux::Window::~Window(){
    X11Handle* h = (X11Handle*) m_native_handle;

    XDestroyWindow(h->display, h->window);
    XFree(h->visual_info);
    XCloseDisplay(h->display);

    delete h;
}

#endif