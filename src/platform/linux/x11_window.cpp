#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

#include <platform/window.hpp>
#include <core/debug.hpp>

#include <X11/Xutil.h>

Lux::Platform::Window::Window(const System& system, const SurfaceNativeSettings& surface_settings, i32 width, i32 height, const char* title)
    : native(native_)
    , system_(system)
    , close_flag_(false)
    , width(width_)
    , height(height_)
    , width_(width)
    , height_(height)
{
    XVisualInfo visual_info_template = {};
    visual_info_template.visualid = surface_settings.visual_id;

    int num_items;

    XVisualInfo* visual_info = XGetVisualInfo((Display*) system.native.display, VisualIDMask, &visual_info_template, &num_items);

    LUX_VERIFY(visual_info, "failed to get visual info");

    Colormap cmap = XCreateColormap((Display*) system.native.display, XRootWindow((Display*) system.native.display, visual_info->screen), visual_info->visual, AllocNone);

    LUX_VERIFY(cmap, "failed to create color map");

    XSetWindowAttributes swa = {};
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    swa.background_pixel = XBlackPixel((Display*) system.native.display, system.native.screen);
    
    native_.window = XCreateWindow((Display*) system.native.display, XRootWindow((Display*) system.native.display, visual_info->screen), 0, 0, width, height, 0, visual_info->depth, InputOutput, visual_info->visual, CWColormap | CWEventMask | CWBorderPixel, &swa);

    XStoreName((Display*) system.native.display, native.window, title);

    native_.wmDeleteMessage = XInternAtom((Display*) system.native.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols((Display*) system.native.display, native.window, &native_.wmDeleteMessage, 1);

    width_ = width;
    height_ = height;

    XFlush((Display*) system.native.display);

    native_.visual_info = visual_info;
}

bool Lux::Platform::Window::should_close(){
    return close_flag_;
}

bool Lux::Platform::Window::show(){
    if(native.window){

        int def_screen = XDefaultScreen((Display*) system_.native.display);
        int screen_width = XDisplayWidth((Display*) system_.native.display, def_screen);
        int screen_height = XDisplayHeight((Display*) system_.native.display, def_screen);
        
        XMapWindow((Display*) system_.native.display, native.window);

        int x = screen_width/2 - width/2;
        int y = screen_height/2 - height/2;

        XMoveWindow((Display*) system_.native.display, native.window, x, y);

        XEvent e;
        do {
            XNextEvent((Display*) system_.native.display, &e);
        } while (e.type != MapNotify);

        XFlush((Display*) system_.native.display);

        return true;
    }

    return false;
}

void Lux::Platform::Window::poll_events(){
    XEvent event;
    while (XPending((Display*) system_.native.display)) {
        XNextEvent((Display*) system_.native.display, &event);

        if(event.type == ClientMessage){
            if(event.xclient.data.l[0] == native.wmDeleteMessage){
                close_flag_ = true;
            }
        }
    }
}

bool Lux::Platform::Window::close(){
    close_flag_ = true;

    return false;
}

Lux::Platform::Window::~Window(){
    XDestroyWindow((Display*) system_.native.display, native.window);
    XFree(native_.visual_info);
}

#endif