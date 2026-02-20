#pragma once
#include <platform/detect.hpp>

#if     defined(PLATFORM_WINDOWS)
    #include <platform/windows/win32_native.hpp>
#elif   defined(PLATFORM_LINUX)
    #include <platform/linux/x11_native.hpp>
    #include <platform/linux/egl_native.hpp>
#endif
