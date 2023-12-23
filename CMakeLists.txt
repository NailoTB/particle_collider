# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(ParticleSimulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

# Add source files
set(SOURCES
    src/Particle.cpp
    src/Dynamics.cpp
    src/main.cpp
    # Add other source files as needed
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})