#pragma once
#include <atomina.hpp>
#include "MainMenuState.hpp"
#include "GameStateType.hpp"

#ifdef ATOMINA_EXPORTS
#    error Atomina Exports was defined in the game app
#endif

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class GameApp: public ATMA::Game
{
public:
    // default constructor
    GameApp();

    // deconstructor
    ~GameApp();

    /**
     * real implementation of the game apps run function to house the
     * game loop
     */
    virtual void run() override;

    /**
     * real implementation of the game apps shut down function
     * to initiate shut down of the app
     */
    virtual void shutdown() override;
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