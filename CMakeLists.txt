# CMakeLists.txt
cmake_minimum_required(VERSION 3.28.3 FATAL_ERROR)
project(OpenSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SOURCES
	"source/*.cpp"
	"source/*.c"
)
add_executable(OpenSM ${SOURCES})