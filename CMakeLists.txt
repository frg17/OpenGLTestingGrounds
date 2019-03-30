cmake_minimum_required (VERSION 3.13)
project (Trashboi)

add_subdirectory (external)

find_package (OpenGL)
find_package (glfw3)

set (TARGET_SOURCES
    src/main.cpp
    src/entity.cpp
    src/camera.cpp
    src/shader.cpp
)

set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

include_directories (
    src/include/
)


add_executable (Main ${TARGET_SOURCES})
target_link_libraries (Main
    fgutils glfw glad ${OpenGL_LIBRARIES}
)

