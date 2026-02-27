#include "math/matrix4.hpp"
#include "math/vector3.hpp"
#include <core/transform.hpp>

void Lux::Core::Transform::set_position(const Math::Vector3& position){
    position_ = position;
    dirty_ = true;
}

void Lux::Core::Transform::set_rotation(const Math::Vector3& rotation){
    rotation_ = rotation;
    dirty_ = true;
}

void Lux::Core::Transform::set_scale(const Math::Vector3& scale){
    scale_ = scale;
    dirty_ = true;
}

Lux::Math::Vector3 Lux::Core::Transform::get_position(){
    return position_;
}

Lux::Math::Vector3 Lux::Core::Transform::get_rotation(){
    return rotation_;
}

Lux::Math::Vector3 Lux::Core::Transform::get_scale(){
    return scale_;
}

Lux::Math::Matrix4 Lux::Core::Transform::get_matrix(){
    if(dirty_){

        matrix = Math::Matrix4::translate(position_) * Math::Matrix4::rotate(rotation_) * Math::Matrix4::scale(scale_);
        
        dirty_ = false;
    }

    return matrix;
}