#pragma once

namespace Lux::Platform{
    struct SystemHandle{
        void*   hinstance = nullptr;
    };

    struct WindowHandle{
        void*   hwnd      = nullptr;
    };

    struct ContextHandle{
        void*   hglrc                       = nullptr;
        void*   hdc                         = nullptr;
        int     pixel_format                = 0;
        void*   wglCreateContextAttribsARB  = nullptr;
    };

    struct GraphicsRequirements{
        int     pixel_format = 0;
    };
}
