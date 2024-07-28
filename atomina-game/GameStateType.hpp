#pragma once
#include <atomina.hpp>

/**
 * defines all possible states within the shared library
 */
enum class GameStateEnum
{
    COUNT = static_cast<unsigned int>(ATMA::State::COUNT),
    MAINMENU,
    PLAYSTATE,
};

/**
 * wrapper class for State Enum that allows for implicit
 * coversion to unsigned int
 */
class GameStateType
{
public:
    // normal constructor
    GameStateType(const GameStateEnum &l_type): m_type(l_type) {}

    // conversion constructor
    GameStateType(const unsigned int &l_int): m_type(static_cast<GameStateEnum>(l_int)) {}

    // conversion operator
    operator unsigned int()
    {
        return static_cast<unsigned int>(m_type);
    }
private:
    const GameStateEnum m_type;
};
