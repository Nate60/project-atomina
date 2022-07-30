#include "AttributeTestSuite.hpp"

TYPED_TEST_SUITE(AttributeFixture, AttributeTypes);

//Adding an attribute should add it to the context
TYPED_TEST(AttributeFixture, AddAttribute)
{
    TypeParam attr{};
    unsigned int obj = this->ctx.createObject();
    this->addAttribute(obj, attr);
    EXPECT_TRUE(this->ctx.hasAttribute(obj, attr.getType()));
}

//adding an attribute that has not been registered should throw an exception
TEST_F(UntypedAttributeFixture, AddBadAttribute)
{
        ATMA::AttrDrawable attr{};
        auto &ctx = ATMA::ATMAContext::getContext();
        unsigned int obj = ctx.createObject();
        ctx.registerAttributeType<ATMA::AttrDrawable>(0);
        EXPECT_THROW(ctx.addAttribute(obj, 20),ATMA::ValueNotFoundException);
}

//registering an attribute factory to a attribute type that already exists should throw an exception
TEST_F(UntypedAttributeFixture, RegisterDuplicateAttributeType)
{
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.registerAttributeType<ATMA::AttrDrawable>(0);
        EXPECT_THROW(ctx.registerAttributeType<ATMA::AttrControllable>(0),ATMA::RegistrationException);
}   


//adding an attribute to an object larger than the last generated object id should
//throw an exception
TYPED_TEST(AttributeFixture, AddAttributeBadObject)
{
    TypeParam attr{};
    unsigned int obj = 100;
    EXPECT_THROW(this->addAttribute(obj, attr), ATMA::ValueNotFoundException);
}

//adding an attribute to an object that already has that attribute
//should pass
TYPED_TEST(AttributeFixture, AddDuplicateAttribute)
{
    TypeParam attr{};
    unsigned int obj = this->ctx.createObject();
    this->addAttribute(obj, attr);
    this->ctx.addAttribute(obj,attr.getType());
    EXPECT_TRUE(this->ctx.hasAttribute(obj,attr.getType()));
}

TYPED_TEST(AttributeFixture, RemoveAttribute)
{
    TypeParam attr{};
    unsigned int obj = this->ctx.createObject();
    this->addAttribute(obj,attr);
    this->removeAttribute(obj,attr);
    EXPECT_FALSE(this->ctx.hasAttribute(obj,attr.getType()));
}

TYPED_TEST(AttributeFixture, RemoveAttributeBadObject)
{
    TypeParam attr{};
    EXPECT_THROW(this->removeAttribute(10,attr),ATMA::ValueNotFoundException);
}

TYPED_TEST(AttributeFixture, RemoveNonExistentAttribute)
{
    TypeParam attr{};
    unsigned int obj = this->ctx.createObject();
    EXPECT_THROW(this->removeAttribute(obj,attr), ATMA::ValueNotFoundException);
}


TYPED_TEST(AttributeFixture, GetAttribute)
{
    TypeParam attr{};
    unsigned int obj = this->ctx.createObject();
    this->addAttribute(obj, attr);
    std::shared_ptr<TypeParam> result = this->getAttribute(obj, attr);
    EXPECT_EQ(attr.getType(), result.get()->getType());
}

TYPED_TEST(AttributeFixture, GetNonExistentAttribute)
{
    TypeParam attr{};
    EXPECT_THROW(this->getAttribute(0,attr), ATMA::ValueNotFoundException);
}

TEST_F(UntypedAttributeFixture, GetWrongTypeAttribute)
{
        ATMA::AttrDrawable attr{};
        ATMA::AttrControllable attr2{};
        auto &ctx = ATMA::ATMAContext::getContext();
        unsigned int obj = ctx.createObject();
        ctx.registerAttributeType<ATMA::AttrDrawable>(0);
        ctx.registerAttributeType<ATMA::AttrControllable>(1);
        ctx.addAttribute(0, 0);
        ctx.addAttribute(0, 1);
        EXPECT_TRUE(!ctx.getAttribute<ATMA::AttrControllable>(0,0));
}