cd %~dp0%~1\..\
if not exist "vendor\spdlog\build" mkdir vendor\spdlog\build
cd vendor\spdlog\build
cmake ..\ -DCMAKE_INSTALL_PREFIX=%~dp0%~1\..\ext -DCMAKE_CXX_FLAGS="-fpic" -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . 
cd ..\..\..\
if not exist "vendor\sfml\build" mkdir vendor\sfml\build
cd vendor\sfml\build
cmake ..\ -DCMAKE_INSTALL_PREFIX=%~dp0%~1\..\ext -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . 
cd ..\..\..\
if not exist "vendor\googletest\build" mkdir vendor\googletest\build
cd vendor\googletest\build
cmake ..\ -DCMAKE_INSTALL_PREFIX=%~dp0%~1\..\ext -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
cmake --install . 