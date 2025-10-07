# UI Layer CMakeLists.txt

# Gather all C and C++ source files for the UI and the bridge
file(GLOB UI_C_SOURCES "*.c")
file(GLOB UI_CPP_SOURCES "*.cpp")

# Exclude cards.c to prevent multiple definition errors for the bitmap data
list(REMOVE_ITEM UI_C_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/cards.c")

# The main executable is defined here, combining the C and C++ sources
add_executable(xskat ${UI_C_SOURCES} ${UI_CPP_SOURCES})

# The UI layer needs to include headers from the application and domain layers
target_include_directories(xskat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the executable against the application library (which includes the domain)
# and the necessary X11 libraries
target_link_libraries(xskat PRIVATE app_lib ${X11_LIBRARIES})