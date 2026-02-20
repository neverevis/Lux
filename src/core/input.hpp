#pragma once
#include <core/event.hpp>
#include <core/types.hpp>

namespace Lux{
    class Input{
    public:
        static bool key_pressed(Keyboard::Key key);
        static bool mouse_pressed(Mouse::Button mouse_button);
        static i32  mouse_delta_scroll();
        static i32  mouseX();
        static i32  mouseY();

        static void on_event(Event& event);
        static void flush_frame_data();

    private:
        static bool s_keys[512];
        static bool s_mouse[2];
        static i32  s_mouseX;
        static i32  s_mouseY;
        static i32  s_delta_scroll;

        static void keyboard_event(Event& event);
        static void mouse_event(Event& event);
        static void action_event(Event& event);
    };
}