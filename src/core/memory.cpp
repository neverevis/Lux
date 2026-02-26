#include <core/memory.hpp>
#include <cstdlib>

Lux::Core::Arena::Arena(size_t capacity)
    : capacity_(capacity)
    , offset_(0)
    , base(nullptr)
{
    base = (u8*) malloc(capacity);
}

Lux::Core::Arena::~Arena(){
    free(base);
}

void Lux::Core::Arena::reset(){
    offset_ = 0;
}