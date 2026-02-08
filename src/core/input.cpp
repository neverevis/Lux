#include <core/input.h>
#include <print>

bool Lux::Input::s_keys[512] = {};
bool Lux::Input::s_mouse[2] = {};
i32 Lux::Input::s_mouseX = 0;
i32 Lux::Input::s_mouseY = 0;
i32 Lux::Input::s_delta_scroll = 0;


bool Lux::Input::key_pressed(Keyboard::Key key){
    return s_keys[(u32)key];
}

bool Lux::Input::mouse_pressed(Mouse::Button mouse_button){
    return s_mouse[(u8)mouse_button];
}

i32 Lux::Input::mouseX(){
    return s_mouseX;
}

i32 Lux::Input::mouseY(){
    return s_mouseY;
}

void Lux::Input::on_event(Event& event){
    switch(event.type){
        case Event::Type::Keyboard:
            keyboard_event(event);
            break;

        case Event::Type::Mouse:
            mouse_event(event);
            break;

        case Event::Type::Action:
            action_event(event);
            break;
    }
}

void Lux::Input::keyboard_event(Event& event){
    if(event.keyboard.state == Keyboard::State::Pressed){
        s_keys[(u32) event.keyboard.key] = true;
    }
    else{
        s_keys[(u32) event.keyboard.key] = false;
    }
}

void Lux::Input::mouse_event(Event& event){
    if(event.mouse.state == Mouse::State::Pressed){
        s_mouse[(u32) event.mouse.button] = true;
    }
    else if(event.mouse.state == Mouse::State::Released){
        s_mouse[(u32) event.mouse.button] = false;
    }
    else if(event.mouse.state == Mouse::State::Moved){
        s_mouseX = event.mouse.x;
        s_mouseY = event.mouse.y;
    }
    else if(event.mouse.state == Mouse::State::Scrolled){
        s_delta_scroll = event.mouse.delta_scroll;
    }
}

void Lux::Input::action_event(Event& event){

}