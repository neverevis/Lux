#include <core/log.h>

#define MACRO_START do{
#define MACRO_END   }while(0);

#ifdef LUX_DEBUG
    #define LUX_PAUSE() __debugbreak();

    #define LUX_ASSERT(condition, msg, ...)             \
        MACRO_START                                     \
        if(!(condition)){                               \
            LUX_ERROR(msg __VA_OPT__(,) __VA_ARGS__);   \
            __debugbreak();                             \
        }                                               \
        MACRO_END
#else
    #define LUX_ASSERT(condition, msg, ...)
    #define LUX_PAUSE()
#endif

#define LUX_VERIFY(condition, msg, ...)             \
    MACRO_START                                     \
    if(!(condition)){                               \
        LUX_ERROR(msg __VA_OPT__(,) __VA_ARGS__);   \
        LUX_PAUSE()                                 \
        exit(1);                                    \
    }                                               \
    MACRO_END