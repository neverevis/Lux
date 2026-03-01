#pragma once

#include <core/types.hpp>
#include <graphics/data.hpp>

namespace Lux::Graphics{
    struct Material{
        f32 r, g, b, a;
        u32 texture;
    };
}