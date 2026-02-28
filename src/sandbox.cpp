#include "core/application.hpp"
#include <math/vector2.hpp>
#include <vector>
#define COPIES 10
#define SPACE 800/COPIES

using namespace Lux;

class Sandbox : public Core::Application {
public:
    f32 rotation = 0;
    f32 incremental = 0;

    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
    }

    void update() override {
    }

    void render() override {
    u8 buf = get_current_buffer(); 
    
    if (buf == 0) draw_rect({100, 100}, 50, 50, 0, {0,0});
    if (buf == 1) draw_rect({400, 100}, 50, 50, 0, {0,0});
    if (buf == 2) draw_rect({700, 100}, 50, 50, 0, {0,0});
    }
};

int main() {
    Sandbox sandbox(800, 800, "lux");
    sandbox.run();
}