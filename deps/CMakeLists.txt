find_package(Python3 REQUIRED COMPONENTS Interpreter)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

add_subdirectory(googletest)

FetchContent_Declare(
  spdlog
  URL https://github.com/gabime/spdlog/archive/0d8197cc9d935e0c5116de551bec63cd35f3c0ef.zip
)

add_subdirectory(spdlog)

FetchContent_Declare(
	glfw
	URL https://github.com/glfw/glfw/archive/8f470597d625ae28758c16b4293dd42d63e8a83a.zip
)

add_subdirectory(glfw)

FetchContent_Declare(
  extern_glad

  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.27)

add_subdirectory(extern_glad)




