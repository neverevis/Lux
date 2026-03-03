#pragma once
#include <core/types.hpp>

namespace Lux::Math{
    class Vector3{
    public:
        f32 x = 0;
        f32 y = 0;
        f32 z = 0;

        Vector3();
        Vector3(f32 x_, f32 y_, f32 z_);

        void reset();

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);

        Vector3 operator*(f32 scale) const;
        Vector3& operator*=(f32 scale);

        f32 length() const;
        Vector3 normalized() const;
        Vector3 cross(const Vector3& other) const;
        f32 dot(const Vector3& other) const;
    };
}