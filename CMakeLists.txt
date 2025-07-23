# CMakeLists.txt
cmake_minimum_required(VERSION 3.28.3 FATAL_ERROR)
project(OpenSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL3 REQUIRED)

# this is why i always use find_package
if(WIN32)
    message(STATUS "Configuring for Windows")

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Windows x64
        message(STATUS "Target: Windows x64")
        link_directories(${CMAKE_SOURCE_DIR}/lib/x64)
        set(STEAM_API_LIB steam_api64)
    else()
        # Windows x86
        message(STATUS "Target: Windows x86")
        link_directories(${CMAKE_SOURCE_DIR}/lib)
        set(STEAM_API_LIB steam_api)
    endif()

elseif(UNIX AND NOT APPLE)
    message(STATUS "Configuring for Linux")

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Linux x64
        link_directories(${CMAKE_SOURCE_DIR}/lib/x64)
        set(STEAM_API_LIB steam_api)
    else()
        # Linux x86
        link_directories(${CMAKE_SOURCE_DIR}/lib)
        set(STEAM_API_LIB steam_api)
    endif()

elseif(APPLE)
    message(STATUS "Configuring for macOS")
    link_directories(${CMAKE_SOURCE_DIR}/lib/osx)
    set(STEAM_API_LIB steam_api)
endif()

file(GLOB_RECURSE SOURCES
	"source/*.cpp"
	"source/*.c"
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/public)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:IN_DEBUG>
)
target_link_libraries(${PROJECT_NAME}
	${STEAM_API_LIB}
	SDL3::SDL3
)