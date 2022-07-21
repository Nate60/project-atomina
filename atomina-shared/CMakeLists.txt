
cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(Atomina_Shared VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS -std=c++17)
set(Intel_Processor CACHE BOOL "false")
set(SFML_INCLUDE_DIR "../ext/include")
set(spdlog_DIR "../ext/lib/cmake/spdlog")
set(SFML_DIR "../ext/lib/cmake/SFML")
list(APPEND CMAKE_PREFIX_PATH "../ext/")
set(CMAKE_SHARED_LINKER_FLAGS "-L../../../ext/lib")

find_package(spdlog REQUIRED)
find_package(SFML COMPONENTS System Window Graphics Network Audio REQUIRED)


file(GLOB_RECURSE atomina_shared_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_shared_src EXCLUDE REGEX ".*\/cmake\/.*")

add_library(Atomina_Shared SHARED)
 
set_property(TARGET Atomina_Shared PROPERTY POSITION_INDEPENDENT_CODE ON)
set_property(GLOBAL PROPERTY CXX_STANDARD 17)

if(${Intel_Processor})
    target_link_libraries(Atomina_Shared sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog tbb)
else()
    target_link_libraries(Atomina_Shared sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog)
endif()

target_sources(Atomina_Shared PRIVATE ${atomina_shared_src})
target_compile_features(Atomina_Shared PRIVATE cxx_std_17)
