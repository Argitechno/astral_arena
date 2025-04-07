cmake_minimum_required(VERSION 3.10)
project(AstralArena)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the include directory (where header files are located)
include_directories(include)

# Find SFML (make sure SFML is installed)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Recursively include all .cpp files in 'src' and its subdirectories, excluding 'src/test' for development purposes
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "src/test/.*")

# Define the executable (add all .cpp files found in the SOURCES list)
add_executable(astral_arena ${SOURCES})

# Link SFML libraries (graphics, window, system)
target_link_libraries(astral_arena sfml-graphics sfml-window sfml-system)
