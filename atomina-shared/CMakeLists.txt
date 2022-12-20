
cmake_minimum_required(VERSION 3.8)

# set the project name and version
project(Atomina_Shared VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17 FORCE)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(Intel_Processor CACHE BOOL "false")

file(GLOB_RECURSE atomina_shared_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_shared_src EXCLUDE REGEX ".*\/cmake\/.*")

add_library(Atomina_Shared SHARED)
 
set_property(TARGET Atomina_Shared PROPERTY POSITION_INDEPENDENT_CODE ON)

if(MSVC)
  target_compile_options(Atomina_Shared PUBLIC "/ZI")
  target_link_options(Atomina_Shared PUBLIC "/INCREMENTAL")
endif()


target_link_directories(Atomina_Shared PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../lib/${CMAKE_BUILD_TYPE}/)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Shared PROPERTY CXX_STANDARD 17)
endif()

if(${Intel_Processor})
    target_link_libraries(Atomina_Shared sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog tbb)
else()
    target_link_libraries(Atomina_Shared sfml-graphics sfml-window sfml-system sfml-network spdlog::spdlog)
endif()

target_sources(Atomina_Shared PRIVATE ${atomina_shared_src})
target_include_directories(Atomina_Shared PRIVATE "../atomina-shared")
#definition for dll for exports
set_target_properties(Atomina_Shared PROPERTIES COMPILE_DEFINITIONS "ATOMINADLL_EXPORTS")

install(TARGETS Atomina_Shared
        CONFIGURATIONS Debug
        RUNTIME DESTINATION Debug/bin)



