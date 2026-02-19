#include <platform/detect.h>
#ifdef PLATFORM_LINUX

#include <platform/window.h>
#include <core/debug.h>

#include <X11/Xutil.h>

Lux::Platform::Window::Window(const System& system, const GraphicsRequirements& graphics_requirements, i32 width, i32 height, const char* title)
    : m_close_flag(false),
      m_system(system)
{
    Display* display = (Display*) system.get_native_handle().display;
    int screen = system.get_native_handle().screen;

    XVisualInfo visual_info_template = {};
    visual_info_template.visualid = graphics_requirements.visual_id;

    int num_items;

    XVisualInfo* visual_info = XGetVisualInfo(display, VisualIDMask, &visual_info_template, &num_items);

    LUX_VERIFY(visual_info, "failed to get visual info");

    Colormap cmap = XCreateColormap(display, XRootWindow(display, visual_info->screen), visual_info->visual, AllocNone);

    LUX_VERIFY(cmap, "failed to create color map");

    XSetWindowAttributes swa = {};
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;
    swa.background_pixel = XBlackPixel(display, screen);
    
    m_window_handle.window = XCreateWindow(display, XRootWindow(display, visual_info->screen), 0, 0, width, height, 0, visual_info->depth, InputOutput, visual_info->visual, CWColormap | CWEventMask | CWBorderPixel, &swa);

    XStoreName(display, m_window_handle.window, title);

    m_window_handle.wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, m_window_handle.window, &m_window_handle.wmDeleteMessage, 1);

    m_width = width;
    m_height = height;

    XFlush(display);

    m_window_handle.visual_info = visual_info;
}

bool Lux::Platform::Window::should_close(){
    return m_close_flag;
}

bool Lux::Platform::Window::show(){
    if(m_window_handle.window){
        Display* display = (Display*) m_system.get_native_handle().display;

        int def_screen = XDefaultScreen(display);
        int screen_width = XDisplayWidth(display, def_screen);
        int screen_height = XDisplayHeight(display, def_screen);
        
        XMapWindow(display, m_window_handle.window);

        int x = screen_width/2 - m_width/2;
        int y = screen_height/2 - m_height/2;

        XMoveWindow(display, m_window_handle.window, x, y);

        XEvent e;
        do {
            XNextEvent(display, &e);
        } while (e.type != MapNotify);

        XFlush(display);

        return true;
    }

    return false;
}

const Lux::Platform::WindowHandle& Lux::Platform::Window::get_native_handle() const{
    return m_window_handle;
}

void Lux::Platform::Window::poll_events(){
    Display* display = (Display*) m_system.get_native_handle().display;
    XEvent event;
    while (XPending(display)) {
        XNextEvent(display, &event);

        if(event.type == ClientMessage){
            if(event.xclient.data.l[0] == m_window_handle.wmDeleteMessage){
                m_close_flag = true;
            }
        }
    }
}

bool Lux::Platform::Window::close(){
    if(!m_close_flag){
        m_close_flag = true;

        return true;
    }

    return false;
}

Lux::Platform::Window::~Window(){
    Display* display = (Display*) m_system.get_native_handle().display;

    XDestroyWindow(display, m_window_handle.window);
    XFree(m_window_handle.visual_info);
}

#endif