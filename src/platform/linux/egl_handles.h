#pragma once

namespace Lux::Platform{
    struct ContextHandle{
        void* egl_display = nullptr;
        void* egl_config  = nullptr;
        void* egl_context = nullptr;
        void* egl_surface = nullptr;
    };

    struct GraphicsRequirements{
        unsigned long visual_id = 0;
    };
}