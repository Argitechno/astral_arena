cmake_minimum_required(VERSION 3.10)
project(AstralArena VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    src/main.cpp
    src/GameManager.cpp
)

# Platform-specific SFML
if(WIN32)
    set(SFML_DIR "C:/Libraries/SFML-2.5.1/lib/cmake/SFML")  # Update to your SFML CMake folder
endif()

# Dynamic linking
set(SFML_STATIC_LIBRARIES FALSE)
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Windows post-build: copy DLLs from sfml_lib to output bin/
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/sfml_lib/sfml-graphics-2.dll"
        "${CMAKE_SOURCE_DIR}/sfml_lib/sfml-window-2.dll"
        "${CMAKE_SOURCE_DIR}/sfml_lib/sfml-system-2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()
