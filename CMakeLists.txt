# set the project name and version
cmake_minimum_required (VERSION 3.24 FATAL_ERROR)

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

add_compile_definitions(__TBB_DYNAMIC_LOAD_ENABLED=0)

message(STATUS "CMAKE_VERSION = ${CMAKE_VERSION}")
message(STATUS "CMAKE_GENERATOR = ${CMAKE_GENERATOR}")
message(STATUS "C Compiler executable: ${CMAKE_C_COMPILER}")
message(STATUS "CXX Compiler executable: ${CMAKE_CXX_COMPILER}")
message(STATUS "Linker executable: ${CMAKE_LINKER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Binary output directory: ${CMAKE_BINARY_DIR}")
message(STATUS "System Target Architecture: ${CMAKE_SYSTEM_PROCESSOR}")

project(Atomina_Main VERSION 0.1.0)

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

#dependencies
find_package(spdlog CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(GLEW REQUIRED)
find_package(X11 REQUIRED)
if(MSVC)
	find_package(stb REQUIRED)
elseif(UNIX) # for some reason stb using different casing on different OSes
	find_package(Stb REQUIRED)
endif()

include(GoogleTest)

#get include paths for each package
find_path(LIB_DIR lib)
find_path(SPDLOG_INCLUDE spdlog)
find_path(GTEST_INCLUDE gtest)
if(MSVC)
	find_path(GLEW_INCLUDE gl)
elseif(UNIX) # for some reason glew using different casing on different OSes
	find_path(GLEW_INCLUDE GL)
endif()
find_path(FMT_INCLUDE fmt)

message(STATUS "spdlog path: ${SPDLOG_INCLUDE}")
message(STATUS "gtest path: ${GTEST_INCLUDE}")
message(STATUS "GLEW path: ${GLEW_INCLUDE}")
message(STATUS "fmt path: ${FMT_INCLUDE}")

add_subdirectory("atomina-shared" atomina-shared)
add_subdirectory("atomina-game" atomina-game)
add_subdirectory("atomina-test" atomina-test)