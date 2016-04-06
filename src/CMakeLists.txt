# Minimum CMake version required
cmake_minimum_required(VERSION 2.8.11)

# Global name of the project
project(SpaceShooter)

# Version
#set(VERSION_MAJOR 0)
#set(VERSION_MINOR 1)
#set(VERSION_PATCH 0)

## These might come in handy:
 #set(CMAKE_BUILD_TYPE Debug)
 #set(CMAKE_VERBOSE_MAKEFILE on)

# Adjust the CMAKE_MODULE_PATH to include the "local" cmake/Modules directory
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")


#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_definitions(-DQT_PLUGIN -std=c++11)

aux_source_directory(. SRC_LIST)
aux_source_directory(src SRC)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_directories(${GLEW_LIBRARIES})

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

include_directories(headers)

set( HEADERS
        headers/BattleField.hpp
        headers/Camera.hpp
        headers/Clock.hpp
        headers/FpsCounter.hpp
        headers/GameManager.hpp
        headers/Input.hpp
        headers/SceneObject.hpp
        headers/SpaceShip.hpp
        headers/Rock.hpp
        headers/Bullet.hpp
        headers/AdditionalFunction.hpp
)

#include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADERS} ${SRC})

target_link_libraries(${PROJECT_NAME} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

