#pragma once
#include <atomina.hpp>
#include "GameStateType.hpp"
#include "GameEventType.hpp"

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class GameApp: public ATMA::Game
{
public:

    std::shared_ptr<ATMA::AppWindow> m_win;
    std::shared_ptr<ATMA::GLRenderer> m_renderer;
    ATMA::NetworkClient m_conn{ATMA::URL{"127.0.0.1"}, 4734};

    // default constructor
    GameApp();

    // deconstructor
    ~GameApp();

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
