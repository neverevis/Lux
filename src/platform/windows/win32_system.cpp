#include <platform/detect.h>
#ifdef PLATFORM_WINDOWS

#include <platform/system.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

Lux::Platform::System::System(){
    m_system_handle.hinstance = GetModuleHandle(nullptr);
}

Lux::Platform::System::~System() = default;

const Lux::Platform::SystemHandle& Lux::Platform::System::get_native_handle() const{
    return m_system_handle;
}

#endif