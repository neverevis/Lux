#pragma once
#include <core/types.hpp>
#include <core/time.hpp>
#include <memory>

namespace Lux{
    class Application{
        public:
        Lux::Time delta_time;
        
        Application(i32 width, i32 height, const char* title);
        ~Application();
        
        void    run();
        
        virtual void setup() = 0;
        virtual void update() = 0;
        virtual void render() = 0;
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
        
        void loop();
    };
}