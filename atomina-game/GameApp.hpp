#pragma once
#include <atomina.hpp>
#include "GameState.hpp"

#ifdef ATOMINA_EXPORTS
#   error Atomina Exports was defined in the game app
#endif

/*
 * extension of the Game class from atomina-api
 * used as actual implementation
 */
class GameApp: public ATMA::Game
{
public:
    GameApp();
    ~GameApp();
    virtual void run() override;
    virtual void shutdown() override;
};

class ShutDownManager: public ATMA::ObjectEventListener
{
public:
    ShutDownManager(std::function<void()> onShutdown): m_callback(onShutdown) {}

    ~ShutDownManager() {}

    virtual void notify(const ATMA::ObjectEventContext &l_e) override
    {
        m_callback();
    }

    const std::function<void()> m_callback;
};