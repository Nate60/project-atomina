#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include <SFML/System/Vector2.hpp>
#include <optional>

namespace ATMA
{

    class ATMA_API ObjectEventContext
    {
    public:
        ObjectEventContext(const unsigned int &l_objectEventType);
        ~ObjectEventContext();

        const unsigned int m_objectEventType;
        std::optional<std::vector<unsigned int>> m_sourceObjIDs;
        std::optional<std::vector<unsigned int>> m_targetObjIDs;
        std::optional<sf::Vector2i> m_mouse;
    };

}