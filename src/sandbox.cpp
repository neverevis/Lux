#include <core/application.hpp>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Lux::Application(w, h, title){}

    void update(){
    }

    void render(){
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}