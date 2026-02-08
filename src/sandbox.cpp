#include <core/application.h>
#include <print>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title) {};

    void update(){
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::Enter)){
            std::println("Enter");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::Space)){
            std::println("Space");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::Escape)){
            std::println("Escape");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::LAlt)){
            std::println("LAlt");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::RAlt)){
            std::println("RAlt");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::Backspace)){
            std::println("Backspace");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::LShift)){
            std::println("LShift");
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::RShift)){
            std::println("RShift");
        }
    }

    void render(){
    }

};

int main(){
    Game game(800,600,"Sandbox!");

    game.run();
}