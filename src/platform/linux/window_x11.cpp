#include <platform/platform.h>
#ifdef PLATFORM_LINUX

#include <platform/window.h>
#include <core/debug.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>

struct X11Handle{
    Display* display;
    int screen;
    Window window;
    XVisualInfo* visual_info;
};

Lux::Window::Window(int width, int height, const char* title){
    X11Handle* h = new X11Handle{};
    m_native_handle = h;

    XSetWindowAttributes window_attributes = {};

    h->display = XOpenDisplay(nullptr);

    LUX_VERIFY(h->display, "failed to connect to X server");

    int vis_attr[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    h->screen = XDefaultScreen(h->display);

    h->visual_info = glXChooseVisual(h->display, h->screen, vis_attr);

    LUX_VERIFY(h->visual_info, "failed to choose visual info");

    Colormap cmap = XCreateColormap(h->display, XRootWindow(h->display, h->screen), h->visual_info->visual, AllocNone);

    XSetWindowAttributes swa = {};
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    swa.background_pixel = XBlackPixel(h->display, h->screen);
    
    h->window = XCreateWindow(h->display, XRootWindow(h->display, h->screen), 0, 0, width, height, 0, h->visual_info->depth, InputOutput, h->visual_info->visual, CWColormap | CWEventMask | CWBackPixel, &swa);

    XStoreName(h->display, h->window, title);

    Atom wm_delete = XInternAtom(h->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(h->display, h->window, &wm_delete, 1);

    XMapWindow(h->display, h->window);

    XEvent e;
    do {
        XNextEvent(h->display, &e);
    } while (e.type != MapNotify);

    XFlush(h->display);
}

void Lux::Window::poll_events(){
    X11Handle* h = (X11Handle*) m_native_handle;
    XEvent ev;
    while (XPending(h->display)) {
        XNextEvent(h->display, &ev);
    }
}

Lux::Window::~Window(){
    X11Handle* h = (X11Handle*) m_native_handle;

    XDestroyWindow(h->display, h->window);
    XFree(h->visual_info);
    XCloseDisplay(h->display);

    delete h;
}

#endif