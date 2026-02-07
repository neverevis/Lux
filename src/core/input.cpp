#include <core/input.h>
#include <print>

bool Lux::Input::s_keys[512] = {};
bool Lux::Input::s_mouse[2] = {};
i32 Lux::Input::s_mouseX = 0;
i32 Lux::Input::s_mouseY = 0;


bool Lux::Input::key_pressed(Key key){
    return s_keys[(int)key];
}

bool Lux::Input::mouse_pressed(Mouse::Button mouse_button){
    return false;
}

i32 Lux::Input::mouseX(){
    return s_mouseX;
}

i32 Lux::Input::mouseY(){
    return s_mouseY;
}

void Lux::Input::on_event(Event& event){
    if(event.event_type == EventType::KeyPressed){
        s_keys[(int)event.key] = true;
    }
    else if(event.event_type == EventType::KeyReleased){
        s_keys[(int)event.key] = false;
    }
    else if(event.event_type == Event::Type::MousePressed){
        s_mouse[(int)event.mouse_button] = true;
    }
    else if(event.event_type == EventType::MouseReleased){
        s_mouse[(int)event.mouse_button] = false;
    }
    else if(event.event_type == EventType::MouseMoved){
        s_mouseX = event.mouse.x;
        s_mouseY = event.mouse.y;
    }
}