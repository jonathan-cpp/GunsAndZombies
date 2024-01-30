@echo off
cls

echo Removing the existing Bin and Build directory...
rmdir /s /q Bin
rmdir /s /q Build

echo Running CMake configuration...
cmake -B Build -G "Visual Studio 17 2022"

echo Build completed.

pause