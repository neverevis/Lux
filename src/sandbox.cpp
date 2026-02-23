#include <core/application.hpp>

class Game : public Lux::Application{
public:
    int x, y;
    bool up = true;
    Game(i32 w, i32 h, const char* title) 
        : Lux::Application(w, h, title)
        {}

    void setup(){
        x = 400;
        y = 400;
    }

    void update(){
        if(x <= 100){
            up = true;
        }else if(x >= 700){
            up = false;
        }

        if(up){
            x+= 20;
        }else{
            x-= 20;
        }
    }

    void render(){
        renderer->render_quad(x, y);
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}