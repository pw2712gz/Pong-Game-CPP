cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PongGame)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the SFML directory paths (Homebrew installs SFML here on Apple Silicon)
set(SFML_DIR "/opt/homebrew/opt/sfml/lib/cmake/SFML")

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable
add_executable(PongGame src/main.cpp)

# Link the SFML libraries
target_link_libraries(PongGame sfml-graphics sfml-window sfml-system)
