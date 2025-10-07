# This CMakeLists.txt adds the subdirectories for each layer.
# The order is important to ensure dependencies are available.

add_subdirectory(domain)
add_subdirectory(application)
add_subdirectory(ui)