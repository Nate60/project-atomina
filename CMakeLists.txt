# set the project name and version
cmake_minimum_required (VERSION 3.8)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
		cmake_policy(SET CMP0135 NEW)
endif()



if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
		cmake_policy(SET CMP0048 NEW)
endif()

project(Atomina_Main VERSION 0.1)

set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE ON) # spdlog will not compile without this
# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.

#dependencies 

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
  spdlog
  URL https://github.com/gabime/spdlog/archive/0d8197cc9d935e0c5116de551bec63cd35f3c0ef.zip
)

FetchContent_Declare(
  sfml
  URL https://github.com/SFML/SFML/archive/c6f7fcaa2a1924e6ef6dfee9797ec65decea6a60.zip
)

FetchContent_Declare(
	tbb
	URL https://github.com/wjakob/tbb/archive/9e219e24fe223b299783200f217e9d27790a87b0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 17 FORCE)

FetchContent_MakeAvailable(googletest sfml spdlog tbb)

message(STATUS "this is the cmake binary dir ${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}")

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("atomina-shared" atomina-shared)
add_subdirectory("atomina-game" atomina-game)
add_subdirectory("atomina-test" atomina-test)