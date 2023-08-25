cmake_minimum_required(VERSION 3.0.0)
project(bvh_viewer VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

# Always Pu
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(GLUT REQUIRED)

add_executable(bvh_viewer 
    src/main.cpp
    src/parse_bvh.cpp
    src/parse_bvh.h
    #src/stb_image.h
    )

add_subdirectory(dependencies/imgui/)

target_include_directories(bvh_viewer
    PRIVATE dependencies/imgui)

target_link_directories(bvh_viewer BEFORE
    PUBLIC dependencies/imgui/
    )

target_link_libraries(bvh_viewer 
    glfw
    GLUT::GLUT
    OpenGL::GL
    OpenGL::GLU
    glm::glm
    imgui
    #stb_image
    )