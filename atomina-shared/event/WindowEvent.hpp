#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    class ATMA_API WindowEvent
    {
    public:
        const sf::Event m_event{};

        WindowEvent();
        WindowEvent(sf::Event &l_e);
        ~WindowEvent();

    };

}