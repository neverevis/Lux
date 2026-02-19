#include <platform/detect.h>
#ifdef PLATFORM_WINDOWS

#include <platform/system.h>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

Lux::Platform::System::System(){
    m_system_data.hinstance = GetModuleHandleW(nullptr);
}

Lux::Platform::System::~System() = default

#endif