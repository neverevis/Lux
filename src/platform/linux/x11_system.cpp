#include <platform/detect.h>
#ifdef PLATFORM_LINUX

#include <platform/system.h>

#include <X11/Xlib.h>

Lux::Platform::System::System(){
    m_system_handle.display = XOpenDisplay(nullptr);
    m_system_handle.screen = XDefaultScreen((Display*) m_system_handle.display);
}

Lux::Platform::System::~System(){
    XCloseDisplay((Display*) m_system_handle.display);
}

#endif