#include <math/vector2.hpp>

Lux::Math::Vector2::Vector2(f32 x_, f32 y_)
    : x(x_)
    , y(y_)
{}

Lux::Math::Vector2 Lux::Math::Vector2::operator+(const Vector2& other) const{
    return Lux::Math::Vector2 (x + other.x, y + other.y);
}

Lux::Math::Vector2 Lux::Math::Vector2::operator-(const Vector2& other) const{
    return Lux::Math::Vector2(x - other.x, y - other.y);
}

Lux::Math::Vector2& Lux::Math::Vector2::operator+=(const Vector2& other){
    x += other.x;
    y += other.y;

    return *this;
}

Lux::Math::Vector2& Lux::Math::Vector2::operator-=(const Vector2& other){
    x -= other.x;
    y -= other.y;

    return *this;
}

Lux::Math::Vector2 Lux::Math::Vector2::operator*(f32 scale) const{
    return Lux::Math::Vector2(x * scale, y * scale);
}

Lux::Math::Vector2& Lux::Math::Vector2::operator*=(f32 scale){
    x *= scale;
    y *= scale;

    return *this;
}