#pragma once

#include <core/types.hpp>

namespace Lux{
    class Time{
    private:
        i64 m_nanoseconds;
    public:
        Time();
        Time(i64 nanoseconds);

        static Time now();

        f32 as_seconds();
        f32 as_milliseconds();
        i64 as_nanoseconds();

        Time operator+(const Time& other) const;
        Time operator-(const Time& other) const;
        Time operator*(const Time& other) const;
        Time operator/(const Time& other) const;

        Time operator+=(const Time&  other);
        Time operator-=(const Time&  other);
        Time operator*=(const Time&  other);
        Time operator/=(const Time&  other);

        Time operator=(const Time& other);
    };
}