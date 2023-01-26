#include "StateTestSuite.hpp"

/**
 * Adding a state gives a coresponding id
 */
TEST_F(StateFixture, CanAddState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_TRUE(this->ctx.hasState(id));
}

/**
 * Adding a state to the context with an id that already has a state
 * assigned should throw an exception
 */
TEST_F(StateFixture, AddDuplicateState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    std::unique_ptr<TestState> state2{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_THROW(this->ctx.addState(id, std::move(state2)), ATMA::RegistrationException);
}

/**
 * Removing an id with no registered state should throw an exception
 */
TEST_F(StateFixture, RemoveNonExistentState)
{
    EXPECT_THROW(this->ctx.removeState(0u), ATMA::ValueNotFoundException);
}

/**
 * Switching to an id with no registered state should throw an exception
 */
TEST_F(StateFixture, SwitchToNonExistentState)
{
    EXPECT_THROW(this->ctx.switchToState(0u), ATMA::ValueNotFoundException);
}

/**
 * Context should no longer retain a state once it has been removed
 */
TEST_F(StateFixture, CanRemoveState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_TRUE(this->ctx.hasState(id));
    this->ctx.removeState(id);
    EXPECT_FALSE(this->ctx.hasState(id));
}

/**
 * Systems can be disabled when states are switched
 */
TEST_F(StateFixture, OnStateChangeCanDisableSystem)
{
    std::unique_ptr<TestState> state{new TestState{}};
    ;
    std::unique_ptr<ATMA::DummyState> dummyState{new ATMA::DummyState{}};
    auto stateType = state->getId();
    auto dummyType = dummyState->getId();
    auto sysType = TestSystem{}.getType();
    ctx.registerAttributeType<TestAttribute>(0u);
    ctx.addSystemType<TestSystem>(sysType);
    auto obj = ctx.createObject();
    ctx.addAttribute(obj, 0u);
    ctx.addState(stateType, std::move(state));
    ctx.addState(dummyType, std::move(dummyState));
    ctx.switchToState(dummyType);
    ctx.update();
    EXPECT_FALSE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

/**
 * On state change a system may be enabled
 */
TEST_F(StateFixture, OnStateChangeCanEnableSystem)
{
    std::unique_ptr<TestState> state{new TestState{}};
    std::unique_ptr<ATMA::DummyState> dummyState{new ATMA::DummyState{}};
    auto sysType = TestSystem{}.getType();
    auto stateType = state->getId();
    auto dummyType = dummyState->getId();
    ctx.registerAttributeType<TestAttribute>(0u);
    ctx.addSystemType<TestSystem>(sysType);
    auto obj = ctx.createObject();
    ctx.addAttribute(obj, 0u);
    ctx.addState(stateType, std::move(state));
    ctx.addState(dummyType, std::move(dummyState));
    ctx.switchToState(dummyType);
    ctx.update();
    EXPECT_FALSE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
    ctx.switchToState(stateType);
    ctx.update();
    EXPECT_TRUE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}
