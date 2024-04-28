cmake_minimum_required(VERSION 3.15)

# Set the project name and version
project(2048 VERSION 1.0)

# Set the C standard to C11
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Set the directory paths
set(PROJECT_SOURCE_DIR "/Users/yunxiang/Desktop/2048Game/source")
set(PROJECT_BINARY_DIR "/Users/yunxiang/Desktop/2048Game/build")
set(EXECUTABLE_OUTPUT_PATH "/Users/yunxiang/Desktop/2048Game/executable")

# Add compiler flags for warnings
add_library(2048_compiler_flags INTERFACE)

# Control where the static and shared libraries are built
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")

# Add the executable
add_executable(2048Game "${PROJECT_SOURCE_DIR}/2048game.c")

# Link the compiler flags
target_link_libraries(2048Game PUBLIC 2048_compiler_flags)

# Add the include directory
target_include_directories(2048Game PUBLIC "${PROJECT_BINARY_DIR}")

# Install the executable
install(TARGETS 2048Game DESTINATION bin)
