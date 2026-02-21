#include <core/log.hpp>
#include <platform/detect.hpp>

#if defined(COMPILER_MSVC)
    #define LUX_BREAK() __debugbreak()
#elif defined(COMPILER_GCC)
    #define LUX_BREAK() __asm__ volatile("int $3")
#endif

#define MACRO_START do{
#define MACRO_END   }while(0);

#ifdef LUX_DEBUG
    #define LUX_ASSERT(condition, msg, ...)             \
        MACRO_START                                     \
        if(!(condition)){                               \
            LUX_ERROR(msg __VA_OPT__(,) __VA_ARGS__);   \
            LUX_BREAK();                                \
        }                                               \
        MACRO_END
#else
    #define LUX_ASSERT(condition, msg, ...)
#endif

#define LUX_VERIFY(condition, msg, ...)             \
    MACRO_START                                     \
    if(!(condition)){                               \
        LUX_ERROR(msg __VA_OPT__(,) __VA_ARGS__);   \
        LUX_BREAK();                                \
        exit(1);                                    \
    }                                               \
    MACRO_END