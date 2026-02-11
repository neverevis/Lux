#include <core/application.h>
#include <core/log.h>
#include <core/assert.h>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title) {};

    void update(){
        
    }
    
    void render(){
        int x = 1;
        int y = 5;
        LUX_ASSERT(x == 17, "x value = {}, expected 17", x)
        LUX_INFO("{}hello {}world", blue_txt, yellow_txt);
    }

};

int main(){
    Game game(800,600,"Sandbox!");
    game.run();
}