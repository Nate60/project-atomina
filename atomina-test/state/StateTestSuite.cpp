#include "StateTestSuite.hpp"

TEST_F(StateFixture, CanAddState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_TRUE(this->ctx.hasState(id));
}

TEST_F(StateFixture, AddDuplicateState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    std::unique_ptr<TestState> state2{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_THROW(this->ctx.addState(id, std::move(state2)), ATMA::RegistrationException);
}

TEST_F(StateFixture, RemoveNonExistentState)
{
    EXPECT_THROW(this->ctx.removeState(0u), ATMA::ValueNotFoundException);
}

TEST_F(StateFixture, SwitchToNonExistentState)
{
    EXPECT_THROW(this->ctx.switchToState(0u), ATMA::ValueNotFoundException);
}

TEST_F(StateFixture, CanRemoveState)
{
    std::unique_ptr<TestState> state{new TestState{}};
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));
    EXPECT_TRUE(this->ctx.hasState(id));
    this->ctx.removeState(id);
    EXPECT_FALSE(this->ctx.hasState(id));
}

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
