#pragma once
#include "AtominaTest.hpp"

/**
 * Fixture for testing attribute of the Object Attribute System
 */
template<class T>
class AttributeFixture: public ::testing::Test
{
public:
    ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();
protected:
    /**
     * Helper function for adding attribute of the template class
     * @param l_obj id of the object to add the attribute to
     * @param l_attr attribute to add to the obj
     */
    void addAttribute(const unsigned int &l_obj, T &l_attr)
    {
        ctx.registerAttributeType<T>(l_attr.getType());
        ctx.addAttribute(l_obj, l_attr.getType());
    }

    /**
     * Helper function for removing attribute from the context
     * @param l_obj id of the object to remove from
     * @param attr attribute to remove from object
     */
    void removeAttribute(const unsigned int &l_obj, T &l_attr)
    {
        ctx.removeAttribute(l_obj, l_attr.getType());
    }

    /**
     * Helper function to get attribute of template class type from context
     * @param l_obj id of the object to get attribute from
     * @param l_attr attribute to get from object
     * @returns pointer to attribute from object as specfied type
     */
    std::shared_ptr<T> getAttribute(const unsigned int &l_obj, T &l_attr)
    {
        return ctx.getAttribute<T>(l_obj, l_attr.getType());
    }

    /**
     * Cleans up context after each test
     */
    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }
};

/**
 * Fixture for testing Attribute features that do not require all
 * types to be tested
 */
class UntypedAttributeFixture: public ::testing::Test
{
protected:
    /**
     * Cleans up context after each test
     */
    void TearDown() override
    {
        auto &ctx = ATMA::ATMAContext::getContext();
        ctx.purge();
    }
};