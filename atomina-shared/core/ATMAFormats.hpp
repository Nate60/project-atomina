#pragma once
#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/SysBase.hpp"
#include "resource/Resource.hpp"

namespace ATMA
{

    ATMA_API std::ostream& operator<<(std::ostream& os, const std::shared_ptr<AttrBase> a);

    ATMA_API std::ostream& operator<<(std::ostream& os, const std::shared_ptr<SysBase> s);

    ATMA_API std::ostream& operator<<(std::ostream& os, const std::shared_ptr<Resource> r);

    ATMA_API std::ostream& operator<<(std::ostream& os, const ObjectEventContext &e);

    ATMA_API std::ostream& operator<<(std::ostream& os, const  std::shared_ptr<Window> w);

}

