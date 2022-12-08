#include "PropsTest.hpp"
#include "util/AtominaException.hpp"
#include <gtest/gtest.h>

using namespace std::string_literals;

TEST(PropsTest, StoresValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
}

TEST(PropsTest, StoreAndGetAsValue)
{
    ATMA::Props props{};
    props["key"] = "value"s; // must be casted or it won't be the correct type
    EXPECT_TRUE(props.contains("key"));
    EXPECT_EQ("value"s, props.getAs<std::string>("key"));
}

TEST(PropsTest, GetAsNonExistentValueThrowsException)
{
    ATMA::Props props{};
    EXPECT_THROW(props.getAs<std::string>("key"), ATMA::ValueNotFoundException);
}

TEST(PropsTest, StoreAndCheckValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
    EXPECT_EQ("value"s, std::any_cast<std::string>(props["key"]));
}

TEST(PropsTest, GetNonExistValueThrowsException)
{
    ATMA::Props props{};
    EXPECT_THROW(props.remove("key"), ATMA::ValueNotFoundException);
}

TEST(PropsTest, RemoveValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("key"));
    props.remove("key");
    EXPECT_FALSE(props.contains("key"));
}

TEST(PropsTest, IsCaseInsensitve)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_TRUE(props.contains("KeY"));
}

TEST(PropsTest, CanBeCaseSensitve)
{
    ATMA::Props props{true};
    props["key"] = "value"s;
    EXPECT_FALSE(props.contains("KeY"));
}

TEST(PropsTest, ValueOrGivesFoundValue)
{
    ATMA::Props props{};
    props["key"] = "value"s;
    EXPECT_EQ("value"s, props.value_or("key", "notValue"s));
}

TEST(PropsTest, ValueOrGivesOtherValueIfKeyNotFound)
{
    ATMA::Props props{};
    EXPECT_EQ("notValue"s, props.value_or("key", "notValue"s));
}
