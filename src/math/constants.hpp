#pragma once
#include <core/types.hpp>

namespace Lux::Math {

    constexpr f32 PI = 3.14159265358979323846f;
    constexpr f32 DEG2RAD = PI / 180.0f;
    constexpr f32 RAD2DEG = 180.0f / PI;

    inline f32 to_radians(f32 degrees) {
        return degrees * DEG2RAD;
    }

    inline f32 to_degrees(f32 radians) {
        return radians * RAD2DEG;
    }
}