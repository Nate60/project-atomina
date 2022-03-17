# project-atomina
2D Game Engine Project

My Personal Game Engine using Visual Studio 2019 and C++17 

## Dependencies
(Are included with the project as submodules)

SFML 3.x:

https://github.com/SFML/SFML/tree/fab2c93d7a56e85f60e26f065c051630ffff420e

Spdlog 1.9.x:

https://github.com/gabime/spdlog/tree/21413e599a8bae53bb8e49360849bfae32334a72

## Project Setup

As SFML requires CMake to generate the libraries there is some setup involved.

1. run vcvars64.bat (i.e. C:\Program Filex (x86)\Microsoft Visual Studio\2019\Community\VC\Auxillary\Build\vcvars64.bat)
2. create lib directories in project root directory called "extlib" and "dlib"
3. run cmake `cmake -G"NMake Makefiles" ..\atomina-dll\vendor\sfml\ -DCMAKE_BUILD_TYPE="<Debug|Release>"` from either extlib or dlib for release or debug respectively
4. run `nmake` in the same direcory


