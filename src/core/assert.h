#include <core/log.h>

#ifdef LUX_DEBUG
#define LUX_ASSERT(condition, msg, ...)             \
    if(!(condition)){                               \
        LUX_ERROR(msg __VA_OPT__(,) __VA_ARGS__);   \
        __debugbreak();                             \
    }                                               
#else
#define LUX_ASSERT(condition, msg, ...)
#endif   