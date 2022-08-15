#pragma once
#include <atomina.hpp>
#include <gtest/gtest.h>

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class GameTest: public ATMA::Game
{
public:
    GameTest();
    ~GameTest();
    virtual void run() override;
    virtual void shutdown() override;
};
