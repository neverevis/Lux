#pragma once
#include <core/event.h>
#include <core/types.h>

namespace Lux{
    class Input{
    public:
        static bool key_pressed(Keyboard::Key key);
        static bool mouse_pressed(Mouse::Button mouse_button);
        static i32  mouseX();
        static i32  mouseY();

        static void on_event(Event& event);

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