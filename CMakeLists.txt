# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.1.0)

# Project's name
set(PROJECT_NAME cpptbb-demo-app)
project(${PROJECT_NAME})

# Compiling options
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_compile_options(-g -std=c++17 -Wall -Wextra  -Wstrict-aliasing -pedantic -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wno-unused -Wno-variadic-macros -Wno-parentheses -Wno-ctor-dtor-privacy -fdiagnostics-show-option)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# TBB
list(APPEND CMAKE_MODULE_PATH ".")
find_package(TBB REQUIRED)
include_directories("${TBB_INCLUDE_DIRS}")

# The App
include_directories("${PROJECT_SOURCE_DIR}")
file(GLOB_RECURSE APP_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${APP_SOURCES})
target_link_libraries(${PROJECT_NAME} Threads::Threads tbbmalloc tbb)
