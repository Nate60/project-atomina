# list(APPEND VCPKG_TARGET_TRIPLET "x64-windows")

# set the project name and version
project(Atomina_Test VERSION 0.1.5)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20 FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(Intel_Processor CACHE BOOL "false")


file(GLOB_RECURSE atomina_test_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_test_src EXCLUDE REGEX ".*\/cmake\/.*")

enable_testing()

add_executable(Atomina_Test ${atomina_test_src})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Test PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Atomina_Test PUBLIC spdlog::spdlog Atomina_Shared GTest::gtest)

target_include_directories(Atomina_Test PRIVATE "../atomina-shared" "../atomina-test" "${FMT_INCLUDE}" "${SPDLOG_INCLUDE}" "${GTEST_INCLUDE}")

install(TARGETS Atomina_Test
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)

install(TARGETS Atomina_Test
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)

if (MSVC)
    add_custom_command(
        TARGET Atomina_Test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_RUNTIME_DLLS:Atomina_Test> $<TARGET_FILE_DIR:Atomina_Test>
        COMMAND_EXPAND_LISTS
    )
endif ()

