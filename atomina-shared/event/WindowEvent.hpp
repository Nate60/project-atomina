#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * Wrapper for sfml events to help differentiate
     * from internal engine events 
     */
    class ATMA_API WindowEvent
    {
    public:
        const sf::Event m_event{};

        //default constructor
        WindowEvent();

        //constructor specifying internal sfml event
        WindowEvent(sf::Event &l_e);

        //deconstructor
        ~WindowEvent();

    };

}