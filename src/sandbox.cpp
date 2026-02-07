#include <core/application.h>
#include <print>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title) {};

    void update(){
        std::println("x:{}, y:{}", Lux::Input::mouseX(), Lux::Input::mouseY());
    }

    void render(){
    }

};

int main(){
    Game game(800,600,"Sandbox!");

    game.run();
}