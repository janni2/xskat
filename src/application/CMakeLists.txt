# Application Layer CMakeLists.txt

# Gather all source files for the application library
file(GLOB APP_SOURCES "*.cpp")

# Create a static library for the application layer
add_library(app_lib STATIC ${APP_SOURCES})

# The application layer needs to include headers from the domain layer
target_include_directories(app_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the application library against the domain library
target_link_libraries(app_lib PRIVATE domain_lib)