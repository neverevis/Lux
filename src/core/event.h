#pragma once
#include <core/types.h>

namespace Lux{
    struct Keyboard{
        enum class Key{
            Unknown = 0,
            
            A, B, C, D, E, F, G, H, I, J, K, L, M, 
            N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
            
            Num0, Num1, Num2, Num3, Num4, 
            Num5, Num6, Num7, Num8, Num9,
            
            Escape, Space, Enter, Backspace, Tab,

            LShift  ,   RShift, 
            LCtrl   ,   RCtrl, 
            LAlt    ,   RAlt,
            
            Up  , Down, Left, Right,
            
            F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
            
            Delete, PageUp, PageDown, Home, End, Insert
        };

        enum class State{
            Pressed, Released
        };

        Key     key;
        State   state;
    };

    struct Mouse{
        enum class Button{
            Left, Right
        };
        enum class State{
            Pressed, Released, Moved, Scrolled
        };

        Button button;
        State state;

        i32 x;
        i32 y;
        i32 delta_scroll;
    };

    enum class Action{
        Close, Minimize, Restore, Resize, OnFocus, OutFocus
    };

    struct Event{
        enum class Type{
            Keyboard, Mouse, Action
        };

        Type type;

        union{
            Keyboard    keyboard;
            Mouse       mouse;
            Action      action;
        };
    };
}