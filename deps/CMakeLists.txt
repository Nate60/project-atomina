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
  sfml
  URL https://github.com/SFML/SFML/archive/c6f7fcaa2a1924e6ef6dfee9797ec65decea6a60.zip
)

add_subdirectory(sfml)

FetchContent_Declare(
	tbb
	URL https://github.com/wjakob/tbb/archive/9e219e24fe223b299783200f217e9d27790a87b0.zip
)

add_subdirectory(tbb)