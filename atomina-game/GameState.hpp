#pragma once
#include <atomina.hpp>

/**
 * Game Implementation of state to implement a user defined extended state
 * that is external to the engine
 */
class GameState: public ATMA::BaseState
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    // default constructor
    GameState(): BaseState() {}

    /**
     * Game app implementation of onCreate function to be the initialization
     * of the game app user defined objects
     */
    virtual void onCreate() override {}

    /**
     * stub implementation of onDestroy
     */
    virtual void onDestroy() override {}

    /**
     * stub implementation of activate function
     */
    virtual void activate() override {}

    /**
     * stub implementation of deactive function
     */
    virtual void deactivate() override {}

    /**
     * gets state id
     * @returns state id
     */
    virtual unsigned int getId() const override
    {
        return ATMA::StateType(ATMA::State::COUNT);
    }
};