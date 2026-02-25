#include <core/time.hpp>
#include <chrono>

Lux::Core::Time Lux::Core::Time::now(){
    std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
    return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count());
}

Lux::Core::Time::Time() : nanoseconds_(0) {};

Lux::Core::Time::Time(i64 nanoseconds) : nanoseconds_(nanoseconds) {};

f32 Lux::Core::Time::as_seconds(){
    return nanoseconds_ * 1e-9;
}

f32 Lux::Core::Time::as_milliseconds(){
    return nanoseconds_ * 1e-6;
}

i64 Lux::Core::Time::as_nanoseconds(){
    return nanoseconds_;
}

Lux::Core::Time Lux::Core::Time::operator+(const Time& other) const{
    return Lux::Core::Time(nanoseconds_ + other.nanoseconds_);
}

Lux::Core::Time Lux::Core::Time::operator-(const Time& other) const{
    return Lux::Core::Time(nanoseconds_ - other.nanoseconds_);
}

Lux::Core::Time Lux::Core::Time::operator*(const Time& other) const{
    return Lux::Core::Time(nanoseconds_ * other.nanoseconds_);
}

Lux::Core::Time Lux::Core::Time::operator/(const Time& other) const{
    return Lux::Core::Time(nanoseconds_ / other.nanoseconds_);
}

Lux::Core::Time& Lux::Core::Time::operator+=(const Time& other){
    nanoseconds_ += other.nanoseconds_;
    return *this;
}

Lux::Core::Time& Lux::Core::Time::operator-=(const Time& other){
    nanoseconds_ -= other.nanoseconds_;
    return *this;
}

Lux::Core::Time& Lux::Core::Time::operator*=(const Time& other){
    nanoseconds_ *= other.nanoseconds_;
    return *this;
}

Lux::Core::Time& Lux::Core::Time::operator/=(const Time& other){
    nanoseconds_ /= other.nanoseconds_;
    return *this;
}

Lux::Core::Time& Lux::Core::Time::operator=(const Time& other){
    nanoseconds_ = other.nanoseconds_;
    return *this;
}