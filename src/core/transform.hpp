#pragma once
#include <math/matrix4.hpp>
#include <math/vector3.hpp>
#include <core/types.hpp>

namespace Lux::Core{
    class Transform{
    public:
        void set_position(const Math::Vector3& position);
        void set_rotation(const Math::Vector3& rotation);
        void set_scale(const Math::Vector3& scale);
        void set_pivot(const Math::Vector3& pivot);

        Math::Vector3 get_position();
        Math::Vector3 get_rotation();
        Math::Vector3 get_scale();

        Math::Matrix4 get_matrix();

    private:
        Math::Matrix4  matrix;

        Math::Vector3  position_;
        Math::Vector3  rotation_;
        Math::Vector3  scale_;

        Math::Vector3 pivot_;

        bool                dirty_ = false;
    };
}