#include <core/application.hpp>
#include <graphics/shader.hpp>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Lux::Application(w, h, title){}


    void setup(){
        Lux::Shader shader("a", "b");
    }

    void update(){
    }

    void render(){
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}