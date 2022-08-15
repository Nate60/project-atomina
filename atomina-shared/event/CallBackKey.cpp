#include "../pch.hpp"
#include "CallBackKey.hpp"

namespace ATMA{
    bool operator==(const CallBackKey a, const CallBackKey b)
    {
        return a.stateTypeID == b.stateTypeID && a.eventTypeID == b.eventTypeID;
    }
}