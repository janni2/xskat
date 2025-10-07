# Domain Layer CMakeLists.txt

# Gather all source files for the domain library
file(GLOB DOMAIN_SOURCES "*.cpp")

# Create a static library for the domain layer
add_library(domain_lib STATIC ${DOMAIN_SOURCES})

# The domain layer is self-contained, but we can make its headers available
target_include_directories(domain_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})