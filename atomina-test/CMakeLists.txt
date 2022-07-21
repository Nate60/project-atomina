cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(Atomina_Test VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_FLAGS -std=c++17)
set(Intel_Processor CACHE BOOL "false")
set(GTEST_INCLUDE_DIR "../ext/include")
set(SFML_INCLUDE_DIR "../ext/include")
set(spdlog_DIR "../ext/lib/cmake/spdlog")
set(SFML_DIR "../ext/lib/cmake/SFML")
set(CMAKE_EXE_LINKER_FLAGS "-L../../../ext/lib")


file(GLOB_RECURSE atomina_test_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_test_src EXCLUDE REGEX ".*\/cmake\/.*")

find_package(GTest REQUIRED)
find_package(spdlog REQUIRED)
find_package(SFML COMPONENTS System Window Graphics Network Audio REQUIRED)

enable_testing()
add_executable(Atomina_Test ${atomina_test_src})


if(${Intel_Processor})
    target_link_libraries(Atomina_Test sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog Atomina_Shared gtest tbb)
else()
    target_link_libraries(Atomina_Test sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog Atomina_Shared gtest)
endif()

target_include_directories(Atomina_Test PRIVATE "../ext/include" "../atomina-shared")

