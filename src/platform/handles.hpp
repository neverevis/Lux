#pragma once
#include <platform/detect.hpp>

#if     defined(PLATFORM_WINDOWS)
    #include <platform/windows/win32_handles.hpp>
#elif   defined(PLATFORM_LINUX)
    #include <platform/linux/x11_handles.hpp>
    #include <platform/linux/egl_handles.hpp>
#endif
