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
class GameApp: public ATMA::Game
{
public:

    std::shared_ptr<ATMA::AppWindow> m_win;
    std::shared_ptr<ATMA::GLRenderer> m_renderer;

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

/**
 * Manager for handling shutting down of the game app
 * once the shutdown function is called
 */
class ShutDownManager: public ATMA::ObjectEventListener
{
public:
    // constructor defining shutdown function
    ShutDownManager(std::function<void()> onShutdown): m_callback(onShutdown) {}

    // deconstructor
    ~ShutDownManager() {}

    /**
     * notifies the manager to run the given callback function
     * for shutdown
     * @param l_e shut down event
     */
    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {
        m_callback();
    }

    const std::function<void()> m_callback;
};