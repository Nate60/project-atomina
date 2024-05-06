#include "PropsTest.hpp"
#include "util/AtominaException.hpp"
#include <gtest/gtest.h>

using namespace std::string_literals;

/**
 * Props object correctly stores key
*/
TEST(PropsTest, StoresValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
}


/**
 * Able to retrieve value from key once it is stored
*/
TEST(PropsTest, StoreAndGetAsValue)
{
    ATMA::Props props{};
    props["key"] = "value"s; // must be casted or it won't be the correct type
    EXPECT_TRUE(props.contains("key"));
    EXPECT_EQ("value"s, props.getAs<std::string>("key"));
}

/**
 * If a value is not found in the props object an exception is thrown
*/
TEST(PropsTest, GetAsNonExistentValueThrowsException)
{
    ATMA::Props props{};
    EXPECT_THROW(props.getAs<std::string>("key"), ATMA::ValueNotFoundException);
}

/**
 * using the accessor operand the value stored can be retrieved
*/
TEST(PropsTest, StoreAndCheckValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
    EXPECT_EQ("value"s, std::any_cast<std::string>(props["key"]));
}

/**
 * Trying to remove a non-existent value throws an exception
*/
TEST(PropsTest, GetNonExistValueThrowsException)
{
    ATMA::Props props{};
    EXPECT_THROW(props.remove("key"), ATMA::ValueNotFoundException);
}

/**
 * Able to remove a key-value pair from a props object once it has been stored
*/
TEST(PropsTest, RemoveValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
    props.remove("key");
    EXPECT_FALSE(props.contains("key"));
}

/**
 * by default props keys are case insensitive
*/
TEST(PropsTest, IsCaseInsensitve)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("KeY"));
}

/**
 * Props Object can be set to be case sensitive
*/
TEST(PropsTest, CanBeCaseSensitve)
{
    ATMA::Props props{true};
    props["key"] = "value"s;
    EXPECT_FALSE(props.contains("KeY"));
}

/**
 * If key exists in a props object value_or gives found value
*/
TEST(PropsTest, ValueOrGivesFoundValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_EQ("value"s, props.value_or("key", "notValue"s));
}

/**
 * If key does not exist value_or gives the default value
*/
TEST(PropsTest, ValueOrGivesOtherValueIfKeyNotFound)
{
    ATMA::Props props{};
    EXPECT_EQ("notValue"s, props.value_or("key", "notValue"s));
}
