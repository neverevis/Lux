#pragma once
#include <core/types.hpp>

namespace Lux::Math{
    class Vector2{
    public:
        f32 x = 0;
        f32 y = 0;

        Vector2();
        Vector2(f32 x_, f32 y_);

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);

        Vector2 operator*(f32 scale) const;
        Vector2& operator*=(f32 scale);
    };
}