#include <core/application.h>
#include <print>

class Game : public Lux::Application{
public:
    Game(i32 w, i32 h, const char* title) : Application(w,h,title){}

    void update (){
        std::println("{}", delta_time.as_seconds());
    }

    void render(){
    }
};

int main(){
    Game game(800,800,"game");
    game.run();
}