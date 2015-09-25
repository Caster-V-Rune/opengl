cmake_minimum_required(VERSION 3.1)

project(opengl)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

set(CMAKE_CXX_FLAGS "-g -Wall -lglut -lGL -lGLU -lm")
set(SOURCE_FILES lab01/main.cpp)
add_executable(opengl ${SOURCE_FILES})
target_link_libraries(opengl ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )