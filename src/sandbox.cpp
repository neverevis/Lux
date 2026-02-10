#define LUX_DEBUG
#include <core/application.h>
#include <core/log.h>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title) {};

    void update(){
        
    }
    
    void render(){
        int x = 1;
        int y = 5;
        LUX_INFO("test -> {} {}", x, y);
        LUX_WARN("test -> {} {}", x, y);
        LUX_ERROR("test -> {} {}", x, y);
    }

};

int main(){
    Game game(800,600,"Sandbox!");
    game.run();
}