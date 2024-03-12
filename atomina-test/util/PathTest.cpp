#include "PropsTest.hpp"
#include "util/AtominaException.hpp"
#include <gtest/gtest.h>

using namespace std::string_literals;

TEST(PathTest, RelativePathAlwaysFromExe)
{
    ATMA::Path path = ATMA::Path{"dummy"};
    std::string root = ATMA::Path::getRootPath().parent_path().generic_string();
    EXPECT_EQ(root + "/dummy"s, path.toString());
}

TEST(PathTest, RelativeNestedPathAlwaysFromExe)
{
    ATMA::Path path = ATMA::Path{"dummy/foo/bar"};
    std::string root = ATMA::Path::getRootPath().parent_path().generic_string();
    EXPECT_EQ(root + "/dummy/foo/bar"s, path.toString());
}

TEST(PathTest, EmptyPathDefaultsToExePath)
{
    ATMA::Path path = ATMA::Path{""};
    std::string root = ATMA::Path::getRootPath().parent_path().generic_string();
    EXPECT_EQ(root + "/"s, path.toString());
}

TEST(PathTest, AbsolutePathIsUnchanged)
{
    #ifdef _WINDOWS
    ATMA::Path path = ATMA::Path{"C:/abc/a"};
    EXPECT_EQ("C:/abc/a"s, path.toString());
    #elif __linux__
    ATMA::Path path = ATMA::Path{"/abc/a"};
    EXPECT_EQ("/abc/a"s, path.toString());
    #endif
}