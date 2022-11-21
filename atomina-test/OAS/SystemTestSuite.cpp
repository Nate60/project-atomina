#include "SystemTestSuite.hpp"
#include "OAS/Attribute.hpp"
#include "OAS/SysBase.hpp"
#include "OAS/attributes/AttrMouseTrigger.hpp"
#include "event/ObjectEvent.hpp"
#include "event/ObjectEventContext.hpp"
#include "util/Log.hpp"

TYPED_TEST_SUITE(SystemFixture, SystemTypes);

// should be able to add a system to the context
TYPED_TEST(SystemFixture, AddSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    EXPECT_TRUE(this->ctx.hasSystem(sysType));
}

// should not be able to add a system to the context when the context
// already has a system assigned to that ID
TYPED_TEST(SystemFixture, AddDuplicateSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    TypeParam sys2{};
    this->addSystemType(sysType);
    EXPECT_THROW(this->addSystemType(sysType), ATMA::RegistrationException);
}

// Removing system should remove the system from the context
TYPED_TEST(SystemFixture, RemoveSystem)
{
    unsigned int sysType = TypeParam{}.getType();
    this->addSystemType(sysType);
    this->ctx.removeSystem(sysType);
    EXPECT_FALSE(this->ctx.hasSystem(sysType));
}

// Removing a system that has not been registered in the context
// should throw an exception
TYPED_TEST(SystemFixture, RemoveNonExistentSystem)
{
    EXPECT_THROW(this->ctx.removeSystem(0u), ATMA::ValueNotFoundException);
}

// TEST_F(UntypedSystemFixture, CanAddSystemFunctionAsCallback)
// {
//     unsigned int sysType = TestSystem{}.getType();
//     auto &ctx = ATMA::ATMAContext::getContext();
//     ctx.addSystemType<TestSystem>(sysType);
//     auto sys = ctx.getSystem<TestSystem>(sysType);
//     std::function<void(ATMA::EventContext &)> f =
//         std::bind(&TestSystem::doSomething, *sys, std::placeholders::_1);
//     ctx.addCallback(0u, 0u, f);
//     ctx.addEvent(0u, 0u, ATMA::EventContext{});

//     EXPECT_THROW(ctx.update(), ATMA::ValueNotFoundException);
// }

// disabling a system should prevent it from updating any attributes
TEST_F(UntypedSystemFixture, DisableSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    ctx.registerAttributeType<TestAttribute>(0u);
    ctx.addSystemType<TestSystem>(sysType);
    auto obj = ctx.createObject();
    ctx.addAttribute(obj, 0u);
    ctx.disableSystem(sysType);
    ctx.update();
    EXPECT_FALSE(ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

// Adding an attribute that matches an existing system should update the
// atttribute
TEST_F(UntypedSystemFixture, AddAttributeAddsToSystem)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    this->ctx.addSystemType<TestSystem>(sysType);
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

TEST_F(UntypedSystemFixture, AddSystemThatMatchesAttributeShouldUpdateIt)
{
    unsigned int sysType = TestSystem{}.getType();
    this->ctx.registerAttributeType<TestAttribute>(0u);
    auto obj = this->ctx.createObject();
    this->ctx.addAttribute(obj, 0u);
    this->ctx.addSystemType<TestSystem>(sysType);
    this->ctx.update();
    EXPECT_TRUE(this->ctx.getAttribute<TestAttribute>(obj, 0u)->flag);
}

TEST_F(UntypedSystemFixture, GUISystemShouldTriggerWhenMouseOver)
{
    bool flag = false;
    // create and setup state
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMouseMove = [this]() -> void
    {
        ATMA::Props eventProps{};
        eventProps["mousepos"] = sf::Vector2i{0, 0};
        ATMA::ObjectEventContext eCtx{
            ATMA::ObjectEventType(ATMA::ObjectEvent::MouseOver), eventProps};
        ctx.dispatchObjectEvent(eCtx);
    };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));

    // register and setup system
    this->ctx.addSystemType<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    auto sys = this->ctx.getSystem<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    this->ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::MouseOver), sys);

    // create object and register relevant attributes
    auto objID = this->ctx.createObject();
    this->ctx.registerAttributeType<ATMA::AttrMouseRegion>(
        ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );
    this->ctx.registerAttributeType<ATMA::AttrMouseTrigger>(
        ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion));
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger));

    // update the region to have an area
    auto regionAttr = this->ctx.getAttribute<ATMA::AttrMouseRegion>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );
    regionAttr->m_region.height = 2;
    regionAttr->m_region.width = 2;

    // create mouse button released trigger
    auto triggerAttr = this->ctx.getAttribute<ATMA::AttrMouseTrigger>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );
    triggerAttr->m_mouseOverFunc = [&flag](const ATMA::ObjectEventContext &e) -> void
    { flag = true; };

    sf::Event e{};
    e.type = sf::Event::MouseMoved;
    e.mouseMove.x = 20;
    e.mouseMove.y = 20;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(UntypedSystemFixture, GUISystemShouldTriggerWhenMouseClicked)
{
    bool flag = false;
    // create and setup state
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMousePress = [this]() -> void
    {
        ATMA::Props eventProps{};
        eventProps["mousepos"] = sf::Vector2i{0, 0};
        ATMA::ObjectEventContext eCtx{
            ATMA::ObjectEventType(ATMA::ObjectEvent::MousePressed), eventProps};
        ctx.dispatchObjectEvent(eCtx);
    };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));

    // register and setup system
    this->ctx.addSystemType<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    auto sys = this->ctx.getSystem<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    this->ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::MousePressed), sys);

    // create object and register relevant attributes
    auto objID = this->ctx.createObject();
    this->ctx.registerAttributeType<ATMA::AttrMouseRegion>(
        ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );
    this->ctx.registerAttributeType<ATMA::AttrMouseTrigger>(
        ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion));
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger));

    // update the region to have an area
    auto regionAttr = this->ctx.getAttribute<ATMA::AttrMouseRegion>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );
    regionAttr->m_region.height = 2;
    regionAttr->m_region.width = 2;

    // create mouse button released trigger
    auto triggerAttr = this->ctx.getAttribute<ATMA::AttrMouseTrigger>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );
    triggerAttr->m_mousePressFunc = [&flag](const ATMA::ObjectEventContext &e) -> void
    { flag = true; };

    sf::Event e{};
    e.type = sf::Event::MouseButtonPressed;
    e.mouseButton.button = sf::Mouse::Button::Left;
    e.mouseButton.x = 20;
    e.mouseButton.y = 20;
    this->ctx.pushWindowEvent(ATMA::WindowEvent(e));
    EXPECT_TRUE(flag);
}

TEST_F(UntypedSystemFixture, GUISystemShouldTriggerWhenMouseReleased)
{
    bool flag = false;
    // create and setup state
    std::unique_ptr<TestState> state{new TestState{}};
    state->m_onMouseRelease = [this]() -> void
    {
        ATMA::Props eventProps{};
        eventProps["mousepos"] = sf::Vector2i{0, 0};
        ATMA_ENGINE_INFO("State window event handler function called");
        ATMA::ObjectEventContext eCtx{
            ATMA::ObjectEventType(ATMA::ObjectEvent::MouseReleased), eventProps};
        ctx.dispatchObjectEvent(eCtx);
    };
    auto id = state->getId();
    this->ctx.addState(id, std::move(state));

    // register and setup system
    this->ctx.addSystemType<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    auto sys = this->ctx.getSystem<ATMA::SysGUI>(ATMA::SystemType(ATMA::System::GUI));
    this->ctx.addObjectEventListener(ATMA::ObjectEventType(ATMA::ObjectEvent::MouseReleased), sys);

    // create object and register relevant attributes
    auto objID = this->ctx.createObject();
    this->ctx.registerAttributeType<ATMA::AttrMouseRegion>(
        ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );
    this->ctx.registerAttributeType<ATMA::AttrMouseTrigger>(
        ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion));
    this->ctx.addAttribute(objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger));

    // create mouse button released trigger
    auto triggerAttr = this->ctx.getAttribute<ATMA::AttrMouseTrigger>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseTrigger)
    );

    // update the region to have an area
    auto regionAttr = this->ctx.getAttribute<ATMA::AttrMouseRegion>(
        objID, ATMA::AttributeType(ATMA::Attribute::MouseRegion)
    );

    regionAttr->m_region.height = 2;
    regionAttr->m_region.width = 2;
    triggerAttr->m_mouseReleaseFunc = [&flag](const ATMA::ObjectEventContext &e) -> void
    {
        ATMA_ENGINE_INFO("Triggered Function was called");
        flag = true;
    };

    ATMA_ENGINE_INFO("Creating Dummy Window Event");
    sf::Event e{};
    e.type = sf::Event::MouseButtonReleased;
    e.mouseButton.button = sf::Mouse::Button::Left;
    e.mouseButton.x = 20;
    e.mouseButton.y = 20;
    ATMA_ENGINE_INFO("Is State registered {0}", this->ctx.hasState(id));
    this->ctx.pushWindowEvent(ATMA::WindowEvent{e});
    EXPECT_TRUE(flag);
}
