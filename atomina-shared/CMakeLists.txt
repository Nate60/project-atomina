# set the project name and version
project(Atomina_Shared VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20 FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(Intel_Processor CACHE BOOL "false")

file(GLOB_RECURSE atomina_shared_src CONFIGURE_DEPENDS "*.hpp" "*.cpp" "*.glsl")
list(FILTER atomina_shared_src EXCLUDE REGEX ".*\/cmake\/.*")

if(ATMA_USE_OPENGL)
    message(STATUS "ATMA_USE_OPENGL = ${ATMA_USE_OPENGL}")
    add_compile_definitions(ATMA_OPENGL)
endif()

if(MSVC)
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*UnixImpl.cpp")
elseif(UNIX)
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*WinImpl.cpp")
endif() 

add_library(Atomina_Shared SHARED)

set_property(TARGET Atomina_Shared PROPERTY POSITION_INDEPENDENT_CODE ON)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Shared PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Atomina_Shared PUBLIC spdlog::spdlog GLEW::GLEW)


target_sources(Atomina_Shared PRIVATE ${atomina_shared_src})
target_include_directories(Atomina_Shared PRIVATE "../atomina-shared" "${FMT_INCLUDE}" "${SPDLOG_INCLUDE}" "${GLEW_INCLUDE}")
#definition for dll for exports
set_target_properties(Atomina_Shared PROPERTIES COMPILE_DEFINITIONS "ATOMINADLL_EXPORTS")


install(TARGETS Atomina_Shared
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)

install(TARGETS Atomina_Shared
        CONFIGURATIONS Release
        RUNTIME DESTINATION Release/bin)


        add_custom_command(
        TARGET Atomina_Shared POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/res
                ${CMAKE_CURRENT_BINARY_DIR}/../bin/res/)

        add_custom_command(
        TARGET Atomina_Shared POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/atomina-shared/shader
                ${CMAKE_CURRENT_BINARY_DIR}/../bin/shader/)

