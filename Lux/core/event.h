#pragma once
#include <core/types.h>

namespace Lux{
    enum class Key{
        Unknown = 0,
        
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        
        Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,
        
        Escape, Space, Enter, Backspace, Tab,
        LShift, RShift, LCtrl, RCtrl, LAlt, RAlt,
        
        Up, Down, Left, Right,
        
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        
        Delete, PageUp, PageDown, Home, End, Insert
    };

    namespace Mouse{
        enum class Button{
            Left, Right
        };
    }

    enum class EventType{
        KeyPressed, KeyReleased,

        MousePressed, MouseReleased, MouseMoved, MouseScrolled
    };

    struct Event{
        EventType           event_type;

        struct{
            i32 x;
            i32 y;
        }                   mouse;

        union{
            Key             key;
            Mouse::Button   mouse_button;
        };

        f32 scroll_delta;
    };
}