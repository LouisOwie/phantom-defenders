# Projects Settings
cmake_minimum_required (VERSION 3.10)
project (phantom-defenders)

# The main executable
add_executable(phantom-defenders
        src/window/Application.cpp
        src/window/Application.hpp
        src/window/MyApplication.cpp
        src/window/MyApplication.hpp
        src/utils/glError.cpp
        src/utils/glError.hpp
        src/main.cpp
        src/utils/Shader.cpp
        src/utils/Shader.hpp
        src/entities/Camera.cpp
        src/entities/Camera.hpp
        src/entities/Model.cpp
        src/entities/Model.hpp
        src/entities/Mesh.cpp
        src/entities/Mesh.hpp
        src/entities/Light.cpp
        src/entities/Light.hpp
)

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/src/assets)
file(COPY ${ASSETS_DIR} DESTINATION ${CMAKE_BINARY_DIR})

set_property(TARGET phantom-defenders PROPERTY CXX_STANDARD 23)
target_compile_options(phantom-defenders PRIVATE -Wall)

add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)
add_subdirectory(lib/assimp EXCLUDE_FROM_ALL)
add_subdirectory(lib/stb EXCLUDE_FROM_ALL)

target_link_libraries(phantom-defenders
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
  PRIVATE assimp
  PRIVATE stb
)

configure_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/src/asset.hpp.in
  ${CMAKE_CURRENT_BINARY_DIR}/src/asset.hpp
)
target_include_directories(phantom-defenders
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
  PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/src
)
