# CMakeLists.txt for PGE_Platformer (Root Script)

# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.7.2)

# Project name and version
set(PROJECT_NAME ThingyStudios)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Ensure that the "Bin" directory exists (create it if not)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

# Specify the directory for executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

# Specify the output directory for the library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Bin)

set(SERVER_TARGET_NAME Server)
set(CLIENT_TARGET_NAME Client)

add_subdirectory(Server)
add_subdirectory(Client)