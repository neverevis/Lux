#pragma once
#include <platform/detect.h>

#if     defined(PLATFORM_WINDOWS)
    #include <platform/windows/win32_handles.h>
#elif   defined(PLATFORM_LINUX)
    #include <platform/linux/x11_handles.h>
    #include <platform/linux/egl_handles.h>
#endif
