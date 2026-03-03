#include <math/vector3.hpp>
#include <cmath>

Lux::Math::Vector3::Vector3() = default;

Lux::Math::Vector3::Vector3(f32 x_, f32 y_, f32 z_)
    : x(x_)
    , y(y_)
    , z(z_)
{}

void Lux::Math::Vector3::reset(){
    x = 0;
    y = 0;
    z = 0;
}

Lux::Math::Vector3 Lux::Math::Vector3::operator+(const Vector3& other) const{
    return Lux::Math::Vector3 (x + other.x, y + other.y, z + other.z);
}

Lux::Math::Vector3 Lux::Math::Vector3::operator-(const Vector3& other) const{
    return Lux::Math::Vector3(x - other.x, y - other.y, z - other.z);
}

Lux::Math::Vector3& Lux::Math::Vector3::operator+=(const Vector3& other){
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

Lux::Math::Vector3& Lux::Math::Vector3::operator-=(const Vector3& other){
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

Lux::Math::Vector3 Lux::Math::Vector3::operator*(f32 scale) const{
    return Lux::Math::Vector3(x * scale, y * scale, z * scale);
}

Lux::Math::Vector3& Lux::Math::Vector3::operator*=(f32 scale){
    x *= scale;
    y *= scale;
    z *= scale;

    return *this;
}

f32 Lux::Math::Vector3::length() const{
    return sqrtf(x*x + y*y + z*z);
}
 
Lux::Math::Vector3 Lux::Math::Vector3::normalized() const{
    f32 l = length();

    if(l != 0){
        return {x/l, y/l, z/l};
    }

    return {0,0,0};
}

Lux::Math::Vector3 Lux::Math::Vector3::cross(const Vector3& other) const{
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    };
}

f32 Lux::Math::Vector3::dot(const Vector3& other) const{
    return x * other.x + y * other.y + z * other.z;
}