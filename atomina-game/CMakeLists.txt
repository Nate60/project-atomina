# set the project name and version
project(Atomina_Game VERSION 0.1)

set(Intel_Processor CACHE BOOL "false")

file(GLOB_RECURSE atomina_game_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_game_src EXCLUDE REGEX ".*\/cmake\/.*")

set_target_properties(Atomina_Shared PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/../atomina-shared/${CMAKE_BUILD_TYPE}/Atomina_Shared.lib"
)

add_executable(Atomina_Game ${atomina_game_src})


target_link_directories(Atomina_Game PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../lib/${CMAKE_BUILD_TYPE}/)

# "$<LINK_LIBRARY:WHOLE_ARCHIVE,Atomina_Shared>"
target_link_libraries(Atomina_Game spdlog::spdlog Atomina_Shared)


target_include_directories(Atomina_Game PRIVATE "../ext/include" "../atomina-shared")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Atomina_Game PROPERTY CXX_STANDARD 20)
  set_property(TARGET Atomina_Game PROPERTY CMAKE_ENABLE_EXPORTS "true")
endif()



