# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)

project(ParticleCollider)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(include)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
qt_standard_project_setup()
# Add the include directories for Qt
include_directories(${Qt6Widgets_INCLUDE_DIRS})
# Add source files
set(SOURCES
    src/VectorMath.cpp
    src/Particle.cpp
    src/Cell.cpp
    src/CellSpace.cpp
    src/Dynamics.cpp
    src/Fermion.cpp
    src/Boson.cpp
    src/main.cpp
    src/SimulationWindow.cpp
    src/SimulationToolBar.cpp
    include/SimulationWindow.h
    include/SimulationToolBar.h
)

SET(CMAKE_CXX_FLAGS "-O2")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt6::Core)
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)
