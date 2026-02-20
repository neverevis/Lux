#include <platform/detect.hpp>
#ifdef PLATFORM_LINUX

#include <platform/system.hpp>

#include <X11/Xlib.h>

Lux::Platform::System::System()
    : native(native_)
{
    native_.display = XOpenDisplay(nullptr);
    native_.screen = XDefaultScreen((Display*) native.display);
}

Lux::Platform::System::~System(){
    XCloseDisplay((Display*) native.display);
}

const Lux::Platform::SystemHandle& Lux::Platform::System::get_native_handle() const{
    return m_system_handle;
}

#endif