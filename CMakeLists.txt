set(CMAKE_CXX_COMPILER g++-4.9)

cmake_minimum_required(VERSION 3.3.2)
project(3dChess)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Game.cpp Game.h Player.cpp Player.h Piece.cpp Piece.h Board.cpp Board.h Declarations.h Reader.cpp Reader.h Shaderprogram.cpp Shaderprogram.h Cube.cpp Cube.h Model.cpp Model.h lodepng.cpp lodepng.h models/bishop.h models/pawn.h models/king.h models/knight.h models/queen.h models/rook.h)
add_executable(3dChess ${SOURCE_FILES})

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(glfw-3.2)

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



find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIRS})





target_link_libraries(3dChess glfw libglfw3.a ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
