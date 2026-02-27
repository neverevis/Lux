#include "math/vector2.hpp"
#include <core/application.hpp>

#include <memory>
#include <platform/system.hpp>
#include <platform/window.hpp>
#include <platform/graphics_context.hpp>
#include <graphics/renderer.hpp>

#include <core/event.hpp>
#include <core/input.hpp>
#include <print>

struct Lux::Core::Application::Impl{
    Lux::Platform::System           system_;
    Lux::Platform::GraphicsContext  context_;
    Lux::Platform::Window           window_;
    Lux::Graphics::Renderer         renderer_;

    Impl(i32 width, i32 height, const char* title)
        : system_()
        , context_(system_)
        , window_(system_, context_.surface_settings, width, height, title)
        , renderer_((prepare_opengl(), Graphics::Renderer(window_)))
    {}

private:
    void prepare_opengl(){
        context_.create(window_);
        context_.make_current();
        window_.callback_ = Lux::Core::Input::on_event;
        window_.show();
        context_.swap_interval(0);
    }
};

Lux::Core::Application::Application(i32 width, i32 height, const char* title)
    : delta_time()
    , impl_(std::make_unique<Impl>(width, height, title))
{}

Lux::Core::Application::~Application() = default;

void Lux::Core::Application::run(){
    loop();
}

void Lux::Core::Application::loop(){
    setup();
    Time last_time;
    Time current_time;

    last_time = Time::now();
    
    while(!impl_->window_.should_close()){
        current_time = Time::now();
        delta_time = current_time - last_time;
        std::println("{}", delta_time.as_milliseconds());
        last_time = current_time;

        impl_->window_.poll_events();
        impl_->renderer_.begin();
        update();
        render();
        impl_->renderer_.end();
        impl_->context_.swap_buffers();
        Input::flush_frame_data();
    }
}

void Lux::Core::Application::draw_rect(const Math::Vector2& position, u32 width, u32 height, f32 rotation){
    impl_->renderer_.draw_rect(position, width, height, rotation);
}