#include <math/vector3.hpp>

Lux::Math::Vector3::Vector3() = default;

Lux::Math::Vector3::Vector3(f32 x_, f32 y_, f32 z_)
    : x(x_)
    , y(y_)
    , z(z_)
{}

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