# project-atomina
2D Game Engine Project

Version [0.1.1]

My Personal Game Engine using CMake and C++20

Compatible with MSVC and GCC

## Dependencies
All dependencies are managed using vcpkg, while vcpkg itself is a submodule

vcpkg:

https://github.com/Microsoft/vcpkg/tree/08f00b4f017129450e1e04ad943b77a974603645
https://learn.microsoft.com/en-ca/vcpkg/get_started/overview

Spdlog 1.11.0:

https://github.com/gabime/spdlog

GLEW 2.2.0:

https://github.com/nigels-com/glew

stb (used for image loading) 2021-09-10:

https://github.com/nothings/stb


GoogleTest (for the test project only) 1.11.0#5:

https://github.com/gabime/spdlog

GLFW3 3.3.8:

https://github.com/glfw/glfw

## Project Setup

### Windows:

Requires MSVC 2019+

Open Project in MS Visual Studio and build with CMake

### Linux: 

Install the prerequsite libraries:
(
	*  g++-12 
	*  libstdc++-12-dev 
	*  libstdc++-12-doc 
	*  gcc-12 
	*  gcc-12-base 
	*  gcc-12-doc 
	*  xorg-dev 
	*  libgl1-mesa-dev 
	*  libglu1-mesa-dev 
	*  ninja-build
)

Bootstrap and then run vcpkg to install project dependencies
```
./bootstrap-vcpkg.sh
./vcpkg install
```

Create directory out/build

Generate CMake files
```
cmake ../../ -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_BUILD_TYPE=<Release|Debug> -DCMAKE_TOOLCHAIN_FILE="../../deps/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_CONFIGURATION_TYPES=<Release|Debug> -G "Ninja"
```

From `out/build` build

```
run: cmake --build . --config <Release|Debug> -j 4
```

Run either game or test executable

```
./bin/<Atomina_Test|Atomina_Game>
```
