# project-atomina
2D Game Engine Project

My Personal Game Engine using CMake and C++17

Compatible with MSVC and GCC

## Dependencies
(CMake uses FetchContent to build them)

SFML 2.5.x:

https://github.com/SFML/SFML/tree/c6f7fcaa2a1924e6ef6dfee9797ec65decea6a60

Spdlog 1.10.x:

https://github.com/gabime/spdlog/tree/0d8197cc9d935e0c5116de551bec63cd35f3c0ef

Thread Building Blocks (Required for Intel architectures on Windows and Linux) for CMake 2020.2:

https://github.com/wjakob/tbb/tree/9e219e24fe223b299783200f217e9d27790a87b0

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

Run the buildproject.sh script in sbin

Should be able to run rungame.sh or runtests.sh

