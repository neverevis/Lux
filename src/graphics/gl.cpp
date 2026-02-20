#include <graphics/gl.hpp>
#include <platform/gl_loader.hpp>

namespace Lux::Graphics::gl{
    PFNGLCLEARPROC       clear          = nullptr;
    PFNGLCLEARCOLORPROC  clearColor     = nullptr;

    using namespace Lux::Platform;
    bool init(){
        clear       = (PFNGLCLEARPROC)          load_gl_function("glClear");
        clearColor  = (PFNGLCLEARCOLORPROC)     load_gl_function("glClearColor");

        return clear && clearColor;
    }
}