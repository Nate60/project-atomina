#pragma once
#include <atomina.hpp>

/**
 * defines all possible events within the game
 */
enum class GameEventEnum
{
    COUNT = static_cast<unsigned int>(ATMA::ObjectEvent::COUNT),
    GAMEOVER,
    FLAP,
};

/**
 * wrapper class for State Enum that allows for implicit
 * coversion to unsigned int
 */
class GameEventType
{
public:
    // normal constructor
    GameEventType(const GameEventEnum &l_type): m_type(l_type) {}

    // conversion constructor
    GameEventType(const unsigned int &l_int): m_type(static_cast<GameEventEnum>(l_int)) {}

    // conversion operator
    operator unsigned int()
    {
        return static_cast<unsigned int>(m_type);
    }
private:
    const GameEventEnum m_type;
};
