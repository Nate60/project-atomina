#pragma once
#include "AtominaTest.hpp"
#include "StateFixtures.hpp"

class TestState: public ATMA::BaseState
{
public:
    std::function<void()> m_onKeyPress = []() -> void {};
    std::function<void()> m_onKeyRelease = []() -> void {};
    std::function<void()> m_onMousePress = []() -> void {};
    std::function<void()> m_onMouseRelease = []() -> void {};
    std::function<void()> m_onMouseMove = []() -> void {};

    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

    /**
     * Default constructor
     */
    TestState();

    /**
     * Default destructor
     */
    virtual ~TestState();

    /**
     * function to run when the state is registered to the context.
     * Creates relevant objects and enables required systems
     */
    virtual void onCreate() override;

    /**
     * function to run when the state is removed from the context
     * Removes relevant objects and disabled no longer needed systems
     */
    virtual void onDestroy() override;

    /**
     * Function to run when state is switched to and becomes active,
     * to enable relevant systems
     */
    virtual void activate() override;

    /**
     * Function called when the is switched off of or is disabled,
     * to disable relevant systems
     */
    virtual void deactivate() override;

    /**
     * Gives the type id of the state
     * @returns type id of state type
     */
    virtual unsigned int getId() const override
    {
        return 3u;
    }
};