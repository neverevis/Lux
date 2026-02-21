#include <core/application.hpp>
#include <graphics/gl.hpp>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Lux::Application(w, h, title){}

    void update(){
    }

    void render(){
        Lux::Graphics::gl::clearColor(1,0,0,1);
        Lux::Graphics::gl::clear(GL_COLOR_BUFFER_BIT);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}