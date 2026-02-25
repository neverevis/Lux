#include <core/input.hpp>
#include <core/debug.hpp>

bool Lux::Core::Input::s_keys[512] = {};
bool Lux::Core::Input::s_mouse[2] = {};
i32 Lux::Core::Input::s_mouseX = 0;
i32 Lux::Core::Input::s_mouseY = 0;
i32 Lux::Core::Input::s_delta_scroll = 0;


bool Lux::Core::Input::key_pressed(Keyboard::Key key){
    return s_keys[(u32)key];
}

bool Lux::Core::Input::mouse_pressed(Mouse::Button mouse_button){
    return s_mouse[(u8)mouse_button];
}

i32 Lux::Core::Input::mouseX(){
    return s_mouseX;
}

i32 Lux::Core::Input::mouseY(){
    return s_mouseY;
}

i32 Lux::Core::Input::mouse_delta_scroll(){
    return s_delta_scroll;
}

void Lux::Core::Input::on_event(Event& event){
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

void Lux::Core::Input::keyboard_event(Event& event){
    if(event.keyboard.state == Keyboard::State::Pressed){
        s_keys[(u32) event.keyboard.key] = true;
    }
    else{
        s_keys[(u32) event.keyboard.key] = false;
    }
}

void Lux::Core::Input::mouse_event(Event& event){
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

void Lux::Core::Input::action_event(Event& event){

}

void Lux::Core::Input::flush_frame_data(){
    s_delta_scroll = 0;
}