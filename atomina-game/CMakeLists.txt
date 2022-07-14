cmake_minimum_required(VERSION 3.20)

# set the project name and version
project(Atomina_Game VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(Intel_Processor CACHE BOOL "false")
set(SFML_INCLUDE_DIR "ext/include")
set(spdlog_DIR "ext/lib/cmake/spdlog")
set(SFML_DIR "ext/lib/cmake/SFML")
set(CMAKE_EXE_LINKER_FLAGS "-L../../../ext/lib")

file(GLOB_RECURSE atomina_game_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_game_src EXCLUDE REGEX ".*\/cmake\/.*")

find_package(spdlog REQUIRED)
find_package(SFML COMPONENTS System Window Graphics Network Audio REQUIRED)

add_executable(Atomina_Game ${atomina_game_src})

if(${Intel_Processor})
    target_link_libraries(Atomina_Game sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog Atomina_Shared tbb)
else()
    target_link_libraries(Atomina_Game sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog Atomina_Shared)
endif()

target_include_directories(Atomina_Game PRIVATE "../ext/include" "../atomina-shared")
