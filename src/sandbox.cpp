#include "glcorearb.h"
#include <core/application.h>
#include <platform/gl_renderer.h>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Lux::Application::Application(w, h, title){}

    void render(){
        Lux::GLRenderer::ClearColor(0,1,0,1);
        Lux::GLRenderer::Clear(GL_COLOR_BUFFER_BIT);
    }

    void update(){

    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}