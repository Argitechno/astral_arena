cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(AstralArena VERSION 1.0)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the directories for header files
include_directories(include)

# Add the source files
set(SOURCES
    src/main.cpp
    src/GameManager.cpp
    # Add any other source files here
)

# Platform-specific settings
if(WIN32)
    # Windows-specific SFML settings with MinGW
    set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")  # Update this path as necessary
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
elseif(UNIX)
    # Linux-specific SFML settings
    find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)
endif()

# Add executable (this is where you define your target)
add_executable(${PROJECT_NAME} ${SOURCES})

# Now link the required libraries after defining the target
if(WIN32)
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
elseif(UNIX)
    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
endif()

# Set output directories for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
