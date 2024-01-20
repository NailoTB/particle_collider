# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(ParticleSimulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)
# Find the Qt5 package
# find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Add the include directories for Qt
# include_directories(${Qt5Widgets_INCLUDE_DIRS})
# Add source files
set(SOURCES
    src/Particle.cpp
    src/Cell.cpp
    src/CellSpace.cpp
    src/Dynamics.cpp
    src/Fermion.cpp
    src/Boson.cpp
    src/main.cpp
    # Add other source files as needed
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
# target_link_libraries(${PROJECT_NAME} Qt5::Widgets)