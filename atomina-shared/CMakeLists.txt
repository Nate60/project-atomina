# set the project name and version
project(Atomina_Shared VERSION 0.2.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20 FORCE)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB_RECURSE atomina_shared_src CONFIGURE_DEPENDS "*.hpp" "*.cpp" "*.glsl")
list(FILTER atomina_shared_src EXCLUDE REGEX ".*\/cmake\/.*")

if(MSVC)
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*/platform/Linux/.*")
elseif(UNIX)
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*/platform/Win/.*")
endif() 

add_library(Atomina_Shared STATIC)

set_property(TARGET Atomina_Shared PROPERTY POSITION_INDEPENDENT_CODE ON)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Shared PROPERTY CXX_STANDARD 20)
endif()
target_precompile_headers(Atomina_Shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/pch.hpp)
target_link_libraries(Atomina_Shared PUBLIC spdlog::spdlog glfw)
if(ATMA_APP_TYPE STREQUAL "OpenGL")
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*/renderImpl/Dummy/.*")
    target_link_libraries(Atomina_Shared PUBLIC GLEW::GLEW)
else()
    list(FILTER atomina_shared_src EXCLUDE REGEX ".*/renderImpl/OpenGL/.*")
endif()
if(MSVC)
    target_link_libraries(Atomina_Shared PUBLIC RtAudio::rtaudio) 
    target_include_directories(Atomina_Shared PUBLIC "../atomina-shared" "${FMT_INCLUDE}" "${SPDLOG_INCLUDE}" "${GLEW_INCLUDE}") 
elseif(UNIX)
    target_link_directories(Atomina_Shared PUBLIC "${CMAKE_BINARY_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/lib")
    target_link_libraries(Atomina_Shared PUBLIC tbb ${PIPEWIRE_LIBRARIES})
    target_compile_options(Atomina_Shared PUBLIC ${PIPEWIRE_CFLAGS_OTHER})
    target_include_directories(Atomina_Shared PUBLIC "../atomina-shared" "${FMT_INCLUDE}" "${SPDLOG_INCLUDE}" "${GLEW_INCLUDE}" ${PIPEWIRE_INCLUDE_DIRS}) 
endif()

target_sources(Atomina_Shared PRIVATE ${atomina_shared_src})
#definition for dll for exports
set_target_properties(Atomina_Shared PROPERTIES COMPILE_DEFINITIONS "ATOMINADLL_EXPORTS")

message(STATUS "Compile Definitions: ${COMPILE_DEFINITIONS}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "ATMA_APP_TYPE: ${ATMA_APP_TYPE}")

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

