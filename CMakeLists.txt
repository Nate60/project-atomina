cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(Atomina_Main VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS -std=c++17)
set(GTEST_INCLUDE_DIR "ext/include")
set(SFML_INCLUDE_DIR "ext/include")
set(spdlog_DIR "ext/lib/cmake/spdlog")
set(SFML_DIR "ext/lib/cmake/SFML")
list(APPEND CMAKE_PREFIX_PATH "ext/")
#EXECUTE_PROCESS( COMMAND ${CMAKE_CXX_COMPILER} --version OUTPUT_VARIABLE clang_full_version_string )
#string (REGEX REPLACE ".*clang version ([0-9]+\\.[0-9]+).*" "\\1" CLANG_VERSION_STRING ${clang_full_version_string})

set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON) # spdlog will not compile without this
set_property(GLOBAL PROPERTY CXX_STANDARD 17)

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(SFML COMPONENTS System Window Graphics Network Audio REQUIRED)

add_subdirectory("atomina-shared" atomina-shared EXCLUDE_FROM_ALL)
add_subdirectory("atomina-game" atomina-game)
add_subdirectory("atomina-test" atomina-test)