#include <core/application.h>
#include <core/log.h>
#include <core/debug.h>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title) {};

    void update(){
    }
    
    void render(){
    }

};

int main(){
    Game game(800,600,"Sandbox!");
    game.run();
}