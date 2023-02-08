# project-atomina
2D Game Engine Project

My Personal Game Engine using CMake and C++17

Compatible with MSVC and GCC

## Dependencies
(CMake uses FetchContent to build them)

GLFW 3.x:

https://github.com/glfw/glfw/tree/8f470597d625ae28758c16b4293dd42d63e8a83a

Spdlog 1.10.x:

https://github.com/gabime/spdlog/tree/0d8197cc9d935e0c5116de551bec63cd35f3c0ef

GoogleTest (for the test project only) 1.12.1:

https://github.com/google/googletest/tree/03597a01ee50ed33e9dfd640b249b4be3799d395


## Project Setup

### Windows:

Requires MSVC 2019+

Open Project in MS Visual Studio and build with CMake

### Linux: 

Install the prerequsite libraries:
(
	*  g++ 
	*  xorg-dev 
	*  libgl1-mesa-dev 
	*  libx11-dev 
	*  libudev-dev 
	*  libopenal-dev 
	*  libvorbis-dev 
	*  libflac-dev 
	*  libfreetype-dev 
	*  libxrandr-dev 
	*  libogg-dev 
	*  libvorbisenc2 
	*  libvorbisfile3 
	*  libxcursor-dev 
	*  libtbb-dev (For Intel Architecture only)
	*  libbtbb-dev (For Intel Architecture only)
)

Install CMake and Ninja Build Generator

run:
cmake [build-directory] -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_BUILD_TYPE=[build-type] -DCMAKE_CONFIGURATION_TYPES=[build-type] -G "Ninja"

