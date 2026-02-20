#include <platform/detect.hpp>
#ifdef PLATFORM_WINDOWS

#include <platform/system.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

Lux::Platform::System::System()
    : native(native_)
{
    native_.hinstance = GetModuleHandle(nullptr);
}

Lux::Platform::System::~System() = default;
#endif