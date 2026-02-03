#pragma once

namespace Lux{
    class Window{
        public:
        Window(int width, int height, char* title);
        ~Window();

        void show();
        void poll_events();
        bool should_close();
        void swap_buffers();
    };
}