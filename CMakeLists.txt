cmake_minimum_required(VERSION 3.10)
project(xskat
    VERSION 3.0.0
    DESCRIPTION "XSkat - A free implementation of the card game Skat"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compile options for better debugging and warnings
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -gline-tables-only)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_options(-O2 -DNDEBUG)
endif()

# Find required packages
find_package(X11 REQUIRED)
find_package(SDL2 REQUIRED)

# Define source files by layer (layered architecture)
# Domain Layer: Pure game logic
set(DOMAIN_SOURCES
    src/domain/null.cpp       # Null game variant logic
    src/domain/ramsch.cpp     # Ramsch game variant logic
    src/domain/utils.cpp      # Utility functions (random number generation, error handling)
    src/domain/skat_core.cpp  # Core card evaluation and game logic
    src/domain/skat_game.cpp
)

# Application Layer: Business services (settings, i18n, networking)
set(APPLICATION_SOURCES
    src/application/settings.cpp    # Centralized settings management
    src/application/file_manager.cpp # File I/O and configuration management
    src/application/ai_engine.cpp   # AI and computer player logic
    src/application/game_engine.cpp # Game coordination and flow management
    src/application/irc.cpp         # Network communication and IRC protocol
    src/application/text.cpp        # Internationalization and localization
)

# UI Layer: X11 presentation layer
set(UI_SOURCES
    src/ui/bitmaps.cpp        # Graphics assets and card rendering (includes cards.c)
    src/ui/cards.cpp
    src/ui/xio.cpp            # X11 window management and event handling
    src/ui/xdial.cpp          # Dialog management and user interface
    src/ui/sdl_ui.cpp
)

# Main application orchestrator (composition root)
set(CORE_SOURCES
    src/skat.cpp              # Main application entry point and game loop
)

set(XSKAT_SOURCES
    ${DOMAIN_SOURCES}
    ${APPLICATION_SOURCES}
    ${UI_SOURCES}
    ${CORE_SOURCES}
)

# Create executable
add_executable(xskat ${XSKAT_SOURCES})
# Set target properties
set_target_properties(xskat PROPERTIES
    VERSION ${PROJECT_VERSION}
    OUTPUT_NAME xskat
)

# Link libraries
target_link_libraries(xskat PRIVATE ${X11_LIBRARIES} SDL2::SDL2)
target_include_directories(xskat PRIVATE 
    ${X11_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/domain
    ${CMAKE_CURRENT_SOURCE_DIR}/include/application  
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ui
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
