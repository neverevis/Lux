#pragma once

//OS
#if defined(_WIN32)
    #define PLATFORM_WINDOWS
    #define on_windows(x) x
    #define on_linux(x)
    #define on_macos(x)
#elif defined(__linux__)
    #define PLATFORM_LINUX
    #define on_windows(x)
    #define on_linux(x) x
    #define on_macos(x)
#elif defined(__APPLE__)
    #define PLATFORM_APPLE
    #define on_windows(x)
    #define on_linux(x)
    #define on_macos(x) x
#else
    #error "Platform/OS not supported"
#endif

//COMPILER
#if defined(_MSC_VER)
    #define COMPILER_MSVC
#elif defined(__GNUC__)
    #define COMPILER_GCC
#endif