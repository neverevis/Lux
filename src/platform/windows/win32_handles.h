#pragma once

namespace Lux::Platform{
    struct SystemHandle{
        void*   hinstance = nullptr;
    };

    struct WindowHandle{
        void*   hwnd      = nullptr;
    };

    struct ContextHandle{
        void*   hglrc     = nullptr;
    };

    struct GraphicsRequirements{
    };
}
