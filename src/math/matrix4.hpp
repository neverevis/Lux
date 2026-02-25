#pragma once
#include <core/types.hpp>
#include <math/vector3.hpp>

namespace Lux::Math{
    class Matrix4{
    public:
        Matrix4();

        static Matrix4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 far, f32 near);

        Matrix4& translate(const Vector3& vec3);
        Matrix4& rotate(const Vector3& vec3);
        Matrix4& scale(const Vector3& vec3);

        void reset();
        const f32* get_data() const;

        Matrix4 operator*(const Matrix4& other) const;

    private:
        f32 matrix[16];
    };
}