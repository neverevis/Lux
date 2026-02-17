#pragma once
#include <glcorearb.h>

namespace Lux{
    struct GLRenderer{
        GLRenderer() = delete;

        static bool init();

        static PFNGLCLEARCOLORPROC  ClearColor;
        static PFNGLCLEARPROC       Clear;

    private:
        static void* load_fn(const char* fn_name);
    };
}