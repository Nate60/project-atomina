# set the project name and version
project(Atomina_Bench VERSION 0.2.0)

file(GLOB_RECURSE atomina_bench_src CONFIGURE_DEPENDS "*.hpp" "*.cpp")
list(FILTER atomina_bench_src EXCLUDE REGEX ".*\/cmake\/.*")

set_target_properties(Atomina_Shared PROPERTIES
    IMPORTED_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/../atomina-shared/${CMAKE_BUILD_TYPE}/Atomina_Shared.lib"
)

add_executable(Atomina_Bench ${atomina_bench_src})

target_link_directories(Atomina_Bench PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/../lib/${CMAKE_BUILD_TYPE}/)

# "$<LINK_LIBRARY:WHOLE_ARCHIVE,Atomina_Shared>"
target_link_libraries(Atomina_Bench spdlog::spdlog Atomina_Shared)

target_include_directories(Atomina_Bench PRIVATE "../ext/include" "../atomina-shared") 

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Atomina_Bench PROPERTY CXX_STANDARD 20)
    set_property(TARGET Atomina_Bench PROPERTY CMAKE_ENABLE_EXPORTS "true")
endif()



