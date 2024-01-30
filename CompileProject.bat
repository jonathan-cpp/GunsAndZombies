@echo off
cls

echo Changing to Build directory...
cd Build

echo Compiling the project...
cmake --build . --config Debug
cmake --build . --config Release

echo Compile completed.

pause