# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(FibonacciHeaps CXX)

# Set the C++ standard to C++11 (or higher, e.g., C++14/17, as needed for features like std::vector initialization and structure cleanup)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define the source files for the library components
set(HEAP_SOURCES
    minfibheap.cpp
    maxfibheap.cpp
    converter.cpp
    interpreter.cpp
)

# Add an executable target
add_executable(fib_inventory main.cpp ${HEAP_SOURCES})

# Specify include directories (the current directory contains all headers)
target_include_directories(fib_inventory PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Optional: Set output directory for the executable
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)`