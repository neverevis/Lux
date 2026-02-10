#pragma once
#include <print>
#include <format>
#include <core/types.h>

namespace Lux{
    template<typename... Args>
    void log(const char* label, const char* file, i32 line ,std::format_string<Args...> fmt, Args&&... args){
        std::println("<{}> <{} : {}> {}", label, file, line, std::format(fmt, std::forward<Args>(args)...));
    }
}

#if defined(LUX_DEBUG)
#define LUX_INFO(msg, ...)  Lux::log("\033[36minfo\033[0m", __FILE__, __LINE__, msg __VA_OPT__(,) __VA_ARGS__)
#define LUX_WARN(msg, ...)  Lux::log("\033[33mwarn\033[0m", __FILE__, __LINE__, msg __VA_OPT__(,) __VA_ARGS__)
#else
#define LUX_INFO(msg, ...)
#endif
#define LUX_ERROR(msg, ...) Lux::log("\033[31merror\033[0m",__FILE__, __LINE__, msg __VA_OPT__(,) __VA_ARGS__)