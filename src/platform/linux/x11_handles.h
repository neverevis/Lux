#pragma once

namespace Lux::Platform{
    struct SystemHandle{
        void*   display = nullptr;
        int     screen  = 0;
    };

    struct WindowHandle{
        unsigned long   window = 0;
    };
}
