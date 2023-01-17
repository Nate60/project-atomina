SET "PROJECTPATH=%~dp0.."
SET "CURRENTPATH=%cd%"
cd "%PROJECTPATH%"
if not exist "%PROJECTPATH%\out" mkdir "out"
cd "out"
if not exist "%PROJECTPATH%\out\build" mkdir "build"
cd "build"

cmake "../../" -DCMAKE_BUILD_TYPE=%1 -DCMAKE_CONFIGURATION_TYPES=%1 %*
cmake --build . --config %1

cd "%CURRENTPATH%"