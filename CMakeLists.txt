cmake_minimum_required(VERSION 3.10)
project(xskat C)

set(CMAKE_C_STANDARD 99)

find_package(X11 REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(xskat
    skat.c
    ramsch.c
    null.c
    bitmaps.c
    xio.c
    xdial.c
    irc.c
    text.c
)

if(X11_FOUND)
    include_directories(${X11_INCLUDE_DIR})
    # X11 libraries will be linked together with SDL ones if SDL is found,
    # or separately if SDL is not found.
endif()

if(SDL2_FOUND AND SDL2_image_FOUND AND SDL2_ttf_FOUND)
    target_include_directories(xskat PRIVATE ${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})
    target_link_libraries(xskat PRIVATE ${X11_LIBRARIES} SDL2::SDL2 ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})
else()
    # If SDL is not found, link X11 libraries here
    if(X11_FOUND)
        target_link_libraries(xskat PRIVATE ${X11_LIBRARIES})
    endif()
endif()

target_compile_definitions(xskat PRIVATE
    DEFAULT_LANGUAGE="english"
    DEFAULT_IRC_SERVER="irc.fu-berlin.de"
)
