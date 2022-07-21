cd %~dp0%~1\..\
set PATH=%PATH%;%~dp0%~2ext\
echo %PATH%
if not exist "target\release" mkdir target\release
cd target\release
cmake ..\..\
cmake --build .
