#pragma once

namespace Lux::Platform{
    struct SystemNativeData{
        void*   hinstance = nullptr;
    };

    struct WindowNativeData{
        void*   hwnd      = nullptr;
    };

    struct ContextNativeData{
        void*   hglrc                       = nullptr;
        void*   hdc                         = nullptr;
        void*   wglCreateContextAttribsARB  = nullptr;
        void*   wglSwapIntervalEXT          = nullptr;
    };

    struct SurfaceNativeSettings{
        int     pixel_format = 0;
    };
}
