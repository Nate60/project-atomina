#pragma once
#include "core/ATMAContext.hpp"
#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "core/api.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/AttrBase.hpp"

namespace ATMA
{

    using EventTypeID = unsigned int;

    class ATMA_API AttrMouseTrigger: public AttrBase
    {
    public:
        AttrMouseTrigger();
        ~AttrMouseTrigger();

        virtual void readIn(std::stringstream &l_stream) override;

        EventTypeID m_eventType{};
        std::function<void(const ObjectEventContext &)> m_mouseReleaseFunc =
            [](const ObjectEventContext &) -> void {};
        std::function<void(const ObjectEventContext &)> m_mousePressFunc =
            [](const ObjectEventContext &) -> void {};
        std::function<void(const ObjectEventContext &)> m_mouseOverFunc =
            [](const ObjectEventContext &) -> void {};
    };

}