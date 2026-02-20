#include <platform/system.hpp>
#include <platform/graphics_context.hpp>
#include <core/application.hpp>
#include <core/time.hpp>
#include <memory>
#include <platform/window.hpp>

struct Lux::Application::AppImpl{
    Lux::Platform::System           system_;
    Lux::Platform::GraphicsContext  context_;
    Lux::Platform::Window           window_;

    AppImpl(i32 width, i32 height, const char* title)
        : system_(),
          context_(system_),
          window_(system_, context_.surface_settings, width, height, title)
    {}
};

Lux::Application::Application(i32 width, i32 height, const char* title)
    :delta_time(),
     app_impl(std::make_unique<AppImpl>(width, height, title))
{
    app_impl->context_.create(app_impl->window_);
    app_impl->context_.make_current();
    app_impl->window_.callback_ = Lux::Input::on_event;
    app_impl->window_.show();
}

Lux::Application::~Application() = default;

void Lux::Application::run(){
    loop();
}

void Lux::Application::loop(){
    Time last_time;
    Time current_time;

    last_time = Time::now();
    
    while(!app_impl->window_.should_close()){
        current_time = Time::now();
        delta_time = current_time - last_time;
        last_time = current_time;

        app_impl->window_.poll_events();
        update();
        render();
        app_impl->context_.swap_buffers();
        Input::flush_frame_data();
    }
}