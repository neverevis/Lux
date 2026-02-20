#pragma once
#include <platform/native.hpp>

namespace Lux::Platform{
    class System{
    public:
        const SystemNativeData& native;

        System();
        ~System();

    private:
        SystemNativeData native_;
    };
}