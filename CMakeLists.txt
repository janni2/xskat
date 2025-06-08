cmake_minimum_required(VERSION 3.10)
project(xskat C)

set(CMAKE_C_STANDARD 99)

find_package(X11 REQUIRED)

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
    target_link_libraries(xskat PRIVATE ${X11_LIBRARIES})
endif()

target_compile_definitions(xskat PRIVATE
    DEFAULT_LANGUAGE="english"
    DEFAULT_IRC_SERVER="irc.fu-berlin.de"
)
