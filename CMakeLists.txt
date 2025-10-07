cmake_minimum_required(VERSION 3.10)
project(xskat 
    VERSION 3.0.0
    DESCRIPTION "XSkat - A free implementation of the card game Skat"
    LANGUAGES C
)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add compile options for better debugging and warnings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -g)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2 -DNDEBUG)
endif()

# Find required packages
find_package(X11 REQUIRED)

# Define source files
set(XSKAT_SOURCES
    src/skat.c
    src/ramsch.c
    src/null.c
    src/bitmaps.c
    src/xio.c
    src/xdial.c
    src/irc.c
    src/text.c
)

# Create executable
add_executable(xskat ${XSKAT_SOURCES})

# Set target properties
set_target_properties(xskat PROPERTIES
    VERSION ${PROJECT_VERSION}
    OUTPUT_NAME xskat
)

# Link libraries
target_link_libraries(xskat PRIVATE ${X11_LIBRARIES})
target_include_directories(xskat PRIVATE 
    ${X11_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Compile definitions
target_compile_definitions(xskat PRIVATE
    DEFAULT_LANGUAGE="english"
    DEFAULT_IRC_SERVER="irc.fu-berlin.de"
    XSKAT_VERSION="${PROJECT_VERSION}"
)

# Installation rules
install(TARGETS xskat
    RUNTIME DESTINATION bin
)

install(FILES 
    xskat.man 
    DESTINATION share/man/man1
    RENAME xskat.1
)

install(FILES 
    xskat-de.man 
    DESTINATION share/man/de/man1
    RENAME xskat.1
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME "xskat")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
set(CPACK_PACKAGE_CONTACT "Gunter Gerhardt")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)
