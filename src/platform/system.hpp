#pragma once
#include <platform/handles.hpp>

namespace Lux::Platform{
    class System{
    public:
        System();
        ~System();

        const SystemHandle& get_native_handle() const;

    private:
        SystemHandle m_system_handle;
    };
}