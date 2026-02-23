#include "core/event.hpp"
#include "core/input.hpp"
#include <core/application.hpp>

class Game : public Lux::Application{
public:
    f32 x, y;
    f32 xp, yp;
    bool up = true;
    Game(i32 w, i32 h, const char* title) 
        : Lux::Application(w, h, title)
        {}

    void setup(){
        x = 400;
        y = 400;
        xp = 500;
        yp = 500;
    }

    void update(){
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::W)){
            y += 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::A)){
            x -= 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::S)){
            y -= 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::D)){
            x += 300 * delta_time.as_seconds();
        }

        if(Lux::Input::key_pressed(Lux::Keyboard::Key::I)){
            yp += 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::J)){
            xp -= 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::K)){
            yp -= 300 * delta_time.as_seconds();
        }
        if(Lux::Input::key_pressed(Lux::Keyboard::Key::L)){
            xp += 300 * delta_time.as_seconds();
        }
    }

    void render(){
        renderer->render_quad(x, y);
        renderer->render_quad(xp, yp);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}