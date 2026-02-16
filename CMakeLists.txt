# set the project name and version
cmake_minimum_required (VERSION 3.24 FATAL_ERROR)

#policies
# https://cmake.org/cmake/help/latest/prop_tgt/MSVC_RUNTIME_LIBRARY.html
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.15.0")
	message(STATUS "Policy CMP0091 set")
	cmake_policy(SET CMP0091 NEW)
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
	message(STATUS "Policy CMP0135 set")
	cmake_policy(SET CMP0135 NEW)
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.0.0")
	message(STATUS "Policy CMP0048 set")
	cmake_policy(SET CMP0048 NEW)
endif()

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.13.0")
	message(STATUS "Policy CMP0048 set")
	cmake_policy(SET CMP0048 NEW)
endif()


if(UNIX)
    add_compile_options(-std=c++20 -std=gnu++20)
endif()

set(ATMA_APP_TYPE "${ATMA_APP_TYPE}" CACHE STRING "Determines the application type" FORCE)

if(ATMA_APP_TYPE STREQUAL "Server")
	message(STATUS "Adding Server compile definition")
    add_compile_definitions("ATMA_SERVER")
elseif(ATMA_APP_TYPE STREQUAL "OpenGL")
	message(STATUS "Adding OpenGL compile definition")
	add_compile_definitions("ATMA_OPENGL")
else()
	message(STATUS "No app type compile definition")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions("_DEBUG")
endif()


SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
SET(CMAKE_CXX_FLAGS "-Wall")
SET(CMAKE_CXX_FLAGS_DEBUG "-g")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")
message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX Flags Release: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "CXX Flags Debug: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "Binary output directory: ${CMAKE_BINARY_DIR}")
message(STATUS "System Target Architecture: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "Atomina App Type: '${ATMA_APP_TYPE}'")
message(STATUS "Compile Definitions: ${COMPILE_DEFINITIONS}")
message(STATUS "Linux: ${LINUX}")

project(Atomina_Main VERSION 0.2.3)

# Stop in source builds
SET(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

option(ATOMINA_BUILD_TESTS "Build tests" ON)
SET(CMAKE_COLOR_DIAGNOSTICS ON)
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON) # spdlog will not compile without this


# For Windows: Prevent overriding the parent project's compiler/linker settings
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
SET(CMAKE_CXX_STANDARD 20 FORCE)
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
SET(ATOMINA_APP_NAME "Atomina-Engine App")

include(${CMAKE_CURRENT_SOURCE_DIR}/deps/vcpkg/scripts/buildsystems/vcpkg.cmake)
#dependencies
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
if(ATMA_APP_TYPE STREQUAL "OpenGL")
	find_package(GLEW REQUIRED)
endif()
if(MSVC)
	find_package(stb REQUIRED)
  find_package(rtaudio CONFIG REQUIRED)
elseif(UNIX) # for some reason stb using different casing on different OSes
	  find_package(Stb REQUIRED)
    find_package(TBB REQUIRED components tbb)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(PIPEWIRE REQUIRED libpipewire-0.3)
endif()

include(GoogleTest)

#get include paths for each package
find_path(LIB_DIR lib)
find_path(SPDLOG_INCLUDE spdlog)
find_path(GTEST_INCLUDE gtest)
find_path(GLFW_INCLUDE GLFW)
if(ATMA_APP_TYPE STREQUAL "OpenGL")
	if(MSVC)
		find_path(GLEW_INCLUDE gl)
    find_path(RTAUDIO_INCLUDE rtaudio)
	elseif(UNIX) # for some reason glew using different casing on different OSes
		find_path(GLEW_INCLUDE GL)
	endif()
endif()
find_path(FMT_INCLUDE fmt)

message(STATUS "spdlog path: ${SPDLOG_INCLUDE}")
message(STATUS "gtest path: ${GTEST_INCLUDE}")
message(STATUS "GLEW path: ${GLEW_INCLUDE}")
message(STATUS "fmt path: ${FMT_INCLUDE}")
message(STATUS "STB path: ${Stb_INCLUDE_DIR}")
message(STATUS "GLFW path: ${GLFW_INCLUDE}")
message(STATUS "rtaudio path: ${RTAUDIO_INCLUDE}")
message(STATUS "pipewire path: ${PIPEWIRE_INCLUDE_DIRS}")
message(STATUS "pipewire libs: ${PIPEWIRE_LIBRARIES}")
add_subdirectory("atomina-shared" atomina-shared)
add_subdirectory("atomina-game" atomina-game)
add_subdirectory("atomina-test" atomina-test)
add_subdirectory("atomina-bench" atomina-bench)
