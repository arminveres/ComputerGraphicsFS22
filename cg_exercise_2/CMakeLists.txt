cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(glexample)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
set(GLFW_LIBRARIES glfw)
set(GLM_LIBRARIES glm)

# include external dir for glfw
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/../external")
# include_directories(./external/)

include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
include_directories(SYSTEM ${GLFW_INCLUDE_DIRS})

add_compile_definitions(SHADER_DIR="${CMAKE_SOURCE_DIR}/src")

file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNAL_DIR})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW ${GLFW_LIBRARIES})
