#pragma once
#include "AtominaTest.hpp"
#include "StateFixtures.hpp"

class TestState: public ATMA::BaseState
{
public:
    const unsigned int m_id;
    std::function<void()> m_onKeyPress = []() -> void {};
    std::function<void()> m_onKeyRelease = []() -> void {};
    std::function<void()> m_onMousePress = []() -> void {};
    std::function<void()> m_onMouseRelease = []() -> void {};
    std::function<void()> m_onMouseMove = []() -> void {};

    static std::unordered_map<unsigned int, bool> m_flags;

    /**
     * Default constructor
     */
    TestState(ATMA::ATMAContext *l_ctx);

    /**
     * Constructor with id for getting static values
     */
    TestState(ATMA::ATMAContext *l_ctx, const unsigned int &l_id);

    /**
     * Default destructor
     */
    virtual ~TestState();

    /**
     * Function to run when state is switched to and becomes active,
     * to enable relevant systems
     */
    virtual void activate(ATMA::ATMAContext *l_ctx) override;

    /**
     * Function called when the is switched off of or is disabled,
     * to disable relevant systems
     */
    virtual void deactivate(ATMA::ATMAContext *l_ctx) override;

    virtual void handleInput(ATMA::ATMAContext *l_ctx, const ATMA::WindowEvent &l_winEvent) override;

    /**
     * Gives the type id of the state
     * @returns type id of state type
     */
    virtual unsigned int getId() const override
    {
        return 3u;
    }
};
