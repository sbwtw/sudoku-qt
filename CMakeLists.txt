
cmake_minimum_required(VERSION 3.7)

project(sudoku LANGUAGES CXX)

#set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT (${CMAKE_BUILD_TYPE} MATCHES "Debug"))
    set(CMAKE_CXX_FLAGS -O3)
endif ()

file(GLOB SOURCES
    "src/main.cpp"
    "src/cell.cpp"
    "src/gameboard.cpp"
    "src/mainwindow.cpp"
    "src/numpad.cpp")

# Find the library
find_package(PkgConfig REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

# Tell CMake to create the executable
add_executable(sudoku-qt ${SOURCES})
target_include_directories(sudoku-qt PUBLIC "/home/Projects/sudoku/")
target_link_libraries(sudoku-qt PUBLIC
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    "/home/.cache/rust-build/debug/libsudoku.so"
)
