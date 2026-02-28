#include "core/application.hpp"
#include <math/vector2.hpp>
#include <math/constants.hpp>

using namespace Lux;

class Sandbox : public Core::Application {
public:
    Sandbox(i32 width, i32 height, const char* title)
        : Application(width, height, title) {}

    void setup() override {
    }

    void update() override {
    }

    void render() override {
    }
};

int main() {
    Sandbox sandbox(800, 800, "Lux");
    sandbox.run();
}