#ifdef _WINDOWS
#    include "pch.hpp"
#    include "OSContextWinImpl.hpp"

namespace ATMA
{

    OSContextWinImpl::OSContextWinImpl() {}

    OSContextWinImpl::~OSContextWinImpl() {}

    void OSContextWinImpl::setDLLInstanceHandle(const HINSTANCE &l_dllHandle)
    {
        m_dllInstanceHandle = l_dllHandle;
    }

    const HINSTANCE &OSContextWinImpl::getDLLInstanceHandle()
    {
        return m_dllInstanceHandle;
    }

}
#else
#    error Windows implementation included in non-Windows target
#endif