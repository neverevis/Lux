#include <core/application.hpp>
#include <windows.h>
#include <GL/gl.h>


class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Lux::Application(w, h, title){}

    void update(){

    }

    void render(){
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}