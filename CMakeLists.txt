# Projects Settings
cmake_minimum_required (VERSION 3.10)
project (phantom-defenders)

# The main executable
add_executable(phantom-defenders
  src/Application.cpp
  src/Application.cpp
  src/MyApplication.cpp
  src/MyApplication.cpp
  src/glError.hpp
  src/glError.cpp
  src/main.cpp
  src/Shader.hpp
  src/Shader.cpp
)

set_property(TARGET phantom-defenders PROPERTY CXX_STANDARD 23)
target_compile_options(phantom-defenders PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(phantom-defenders
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/asset.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/asset.hpp
)
target_include_directories(phantom-defenders
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
)
