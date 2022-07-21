cd %~dp0%~1\..\
cd vendor\spdlog
rmdir /q /s build
cd ..\..\
cd vendor\sfml
rmdir /q /s build
cd ..\..\
cd vendor\googletest
rmdir /q /s build
cd ..\..\
rmdir /q /s ext