cmake_minimum_required(VERSION 3.20)

project(glexample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  set(CMAKE_DIRNAME "CMake" CACHE INTERNAL "Generic name of the folder with CMake modules")
  list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/${CMAKE_DIRNAME})

  set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")
  set(BINARY_DIR "${CMAKE_SOURCE_DIR}/external")
  set(GLFW_ROOT "${EXTERNAL_DIR}/glfw")

  set(CMAKE_PREFIX_PATH "${EXTERNAL_DIR}/glew")
  set(CMAKE_LIBRARY_PATH "${EXTERNAL_DIR}/glew/lib-win/msvc14/")
endif()


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
set(EXTERNAL_DIR "${CMAKE_SOURCE_DIR}/external")

if(MSVC)
  find_package(GLFW REQUIRED)
else()
  find_package(glfw3 REQUIRED)
  set(GLFW_LIBRARIES glfw)
endif()


include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
include_directories(SYSTEM ${GLFW_INCLUDE_DIRS})

add_compile_definitions(SHADER_DIR="${CMAKE_SOURCE_DIR}/shader")

file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNAL_DIR})
target_link_libraries(${PROJECT_NAME} OpenGL::GL GLEW::GLEW ${GLFW_LIBRARIES})


if(MSVC)
  file(COPY ${EXTERNAL_DIR}/glew/lib-win/msvc14/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/)
  file(COPY ${EXTERNAL_DIR}/glew/lib-win/msvc14/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Debug/)
  file(COPY ${EXTERNAL_DIR}/glew/lib-win/msvc14/glew32.dll DESTINATION ${CMAKE_BINARY_DIR}/Release/)
endif()
