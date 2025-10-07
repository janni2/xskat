cmake_minimum_required(VERSION 3.10)
project(xskat C CXX)

# Set language standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary external packages
find_package(X11 REQUIRED)

# Add the src directory to start the build process for the layers
add_subdirectory(src)

# Global compile definitions (if any)
target_compile_definitions(xskat PRIVATE
    DEFAULT_LANGUAGE="english"
    DEFAULT_IRC_SERVER="irc.fu-berlin.de"
)