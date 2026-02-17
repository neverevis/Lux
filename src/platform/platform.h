#pragma once

//OS
#if defined(_WIN32)
    #define PLATFORM_WINDOWS
#elif defined(__linux__)
    #define PLATFORM_LINUX
#elif defined(__APPLE__)
    #define PLATFORM_APPLE
#else
    #error "Platform/OS not supported"
#endif

//COMPILER
#if defined(_MSC_VER)
    #define COMPILER_MSVC
#elif defined(__GNUC__)
    #define COMPILER_GCC
#endif