#pragma once

#include <memory>

namespace Lux{
    class Window{
    public:
        struct AgnosticData{
            void* slot_a;
            void* slot_b;
        };

        Window(int width, int height, const char* title);
        ~Window();

        bool show();
        bool close();
        void poll_events();
        bool should_close();
        void swap_buffers();
        AgnosticData get_data();
    
    private:
        struct NativeData;
        std::unique_ptr<NativeData> m_data;
    };
}