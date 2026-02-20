#pragma once
#include <glcorearb.h>

namespace Lux::Graphics::gl{
    extern PFNGLCLEARPROC       clear;
    extern PFNGLCLEARCOLORPROC  clearColor;

    bool init();
}