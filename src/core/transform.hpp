#pragma once
#include <math/matrix4.hpp>
#include <math/vector3.hpp>
#include <core/types.hpp>

namespace Lux::Core{
    class Transform{
    public:
        void set_position(const Lux::Math::Vector3& position);
        void set_rotation(const Lux::Math::Vector3& rotation);
        void set_scale(const Math::Vector3& scale);

        Math::Vector3 get_position();
        Math::Vector3 get_rotation();
        Math::Vector3 get_scale();

        Math::Matrix4 get_matrix();

    private:
        Math::Matrix4  matrix;

        Math::Vector3  position_;
        Math::Vector3  rotation_;
        Math::Vector3  scale_;

        bool                dirty_ = false;
    };
}