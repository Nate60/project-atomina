cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(Atomina_Test VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20 FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(Intel_Processor CACHE BOOL "false")


file(GLOB_RECURSE atomina_test_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_test_src EXCLUDE REGEX ".*\/cmake\/.*")

enable_testing()

add_executable(Atomina_Test ${atomina_test_src})

target_link_libraries(Atomina_Test spdlog::spdlog Atomina_Shared gtest)

target_link_directories(Atomina_Test PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../lib/${CMAKE_BUILD_TYPE}/)

target_include_directories(Atomina_Test PRIVATE "../atomina-shared" "../atomina-test")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Test PROPERTY CXX_STANDARD 20)
endif()
