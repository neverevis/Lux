#pragma once

namespace Lux::Platform{
    struct SystemHandle{
        void*   display = nullptr;
        int     screen  = 0;
    };

    struct WindowHandle{
        unsigned long   window = 0;
        unsigned long   wmDeleteMessage = 0;
        void* visual_info = nullptr;
    };
}
