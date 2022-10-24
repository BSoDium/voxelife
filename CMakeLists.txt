cmake_minimum_required(VERSION 3.10)
project(voxelife 
  VERSION 0.1.0 
  LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(OpenGL_GL_PREFERENCE GLVND)

add_executable(${PROJECT_NAME})

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
)

# Display number of source files found
set(SOURCE_COUNT 0)
foreach(source IN LISTS sources)
    math(EXPR SOURCE_COUNT "${SOURCE_COUNT} + 1")
endforeach()
message(STATUS "Found ${SOURCE_COUNT} source files")


target_link_libraries(${PROJECT_NAME} 
  PRIVATE 
    OpenGL::GL
    OpenGL::GLU
    GLEW::GLEW
    glm::glm
    glfw
)

target_sources(${PROJECT_NAME} PRIVATE ${sources})
