#pragma once

namespace Lux::Platform{
    struct SystemNativeData{
        void*   display = nullptr;
        int     screen  = 0;
    };

    struct WindowNativeData{
        unsigned long   window = 0;
        unsigned long   wmDeleteMessage = 0;
        void* visual_info = nullptr;
    };
}
