#include <core/time.hpp>
#include <chrono>

Lux::Time Lux::Time::now(){
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());
}

Lux::Time::Time() : m_nanoseconds(0) {};

Lux::Time::Time(i64 nanoseconds) : m_nanoseconds(nanoseconds) {};

f32 Lux::Time::as_seconds(){
    return m_nanoseconds * 1e-9;
}

f32 Lux::Time::as_milliseconds(){
    return m_nanoseconds * 1e-6;
}

i64 Lux::Time::as_nanoseconds(){
    return m_nanoseconds;
}

Lux::Time Lux::Time::operator+(const Lux::Time& other) const{
    return Lux::Time(m_nanoseconds + other.m_nanoseconds);
}

Lux::Time Lux::Time::operator-(const Time& other) const{
    return Lux::Time(m_nanoseconds - other.m_nanoseconds);
}

Lux::Time Lux::Time::operator*(const Time& other) const{
    return Lux::Time(m_nanoseconds * other.m_nanoseconds);
}

Lux::Time Lux::Time::operator/(const Time& other) const{
    return Lux::Time(m_nanoseconds / other.m_nanoseconds);
}

Lux::Time Lux::Time::operator+=(const Time&  other){
    m_nanoseconds += other.m_nanoseconds;
    return *this;
}

Lux::Time Lux::Time::operator-=(const Time&  other){
    m_nanoseconds -= other.m_nanoseconds;
    return *this;
}

Lux::Time Lux::Time::operator*=(const Time&  other){
    m_nanoseconds *= other.m_nanoseconds;
    return *this;
}

Lux::Time Lux::Time::operator/=(const Time&  other){
    m_nanoseconds /= other.m_nanoseconds;
    return *this;
}

Lux::Time Lux::Time::operator=(const Time& other){
    m_nanoseconds = other.m_nanoseconds;
    return *this;
}