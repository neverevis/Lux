#pragma once
#include <core/types.hpp>

#include <format>
#include <iostream>

#define reset_txt       "\033[0m"
#define black_txt       "\033[30m"
#define red_txt         "\033[31m"
#define green_txt       "\033[32m"
#define yellow_txt      "\033[33m"
#define blue_txt        "\033[34m"
#define magenta_txt     "\033[35m"
#define cyan_txt        "\033[36m"
#define white_txt       "\033[37m"

namespace Lux{
    template<typename... Args>
    void log(const char* label, const char* label_color, const char* file, i32 line ,std::format_string<Args...> fmt, Args&&... args){
        std::cout << std::format("<{}{}{}> <{}{}{} : {}{}{}> {}{}", label_color, label, reset_txt, black_txt, file, reset_txt, green_txt, line, reset_txt, std::format(fmt, std::forward<Args>(args)...), reset_txt) << std::endl;
    }

    constexpr const char* filename_only(const char* path) {
        const char* file = path;
        while (*path) {
            if (*path == '/' || *path == '\\') file = path + 1;
            path++;
        }
        return file;
    }
}

#if defined(LUX_DEBUG)
#define LUX_INFO(msg, ...)  Lux::log("info", cyan_txt, Lux::filename_only(__FILE__), __LINE__, msg __VA_OPT__(,) __VA_ARGS__)
#define LUX_WARN(msg, ...)  Lux::log("warn", yellow_txt,__FILE__, __LINE__, msg __VA_OPT__(,) __VA_ARGS__)
#else
#define LUX_INFO(msg, ...)
#define LUX_WARN(msg, ...)
#endif
#define LUX_ERROR(msg, ...) Lux::log("error", red_txt,__FILE__, __LINE__, msg __VA_OPT__(,) __VA_ARGS__)