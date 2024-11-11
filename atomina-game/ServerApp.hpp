#pragma once
#include <atomina.hpp>
#include "MainMenuState.hpp"
#include "GameStateType.hpp"
#include "GameEventType.hpp"
#include "PlayState.hpp"
#include "SysFly.hpp"

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class ServerApp: public ATMA::Server
{
public:

    // default constructor
    ServerApp();

    // deconstructor
    ~ServerApp();

    /**
     * real implementation of the game apps setup function to house the setup
     */
    virtual void setup(ATMA::ATMAContext &l_ctx) override;

    /**
     * real implementation of the game apps run function to house the
     * game loop
     */
    virtual void update(ATMA::ATMAContext &l_ctx) override;

    /**
     * real implementation of the game apps shut down function
     * to initiate shut down of the app
     */
    virtual void shutdown(ATMA::ATMAContext &l_ctx) override;
};

