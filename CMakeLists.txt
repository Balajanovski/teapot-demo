cmake_minimum_required(VERSION 3.6)
project(teapot-demo CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake-modules")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-Wall")

# Define no debug
# Comment this out if you want debug mode
add_definitions(-DNDEBUG)

# Find GLFW
find_package(GLFW 3.0.0 REQUIRED)
message("- GLFW Located")
include_directories(${GLFW_INCLUDE_DIR})
if(GLFW_FOUND AND (GLFW_VERSION VERSION_EQUAL 3.0 OR GLFW_VERSION VERSION_GREATER 3.0))
    add_definitions( -DGLFW_VERSION_3 )
endif()

# Find OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    message("- OpenGL Located")
else()
    message("- error: OpenGL not Located")
endif()
include_directories(${OPENGL_HEADER_DIR})

# Find Assimp
find_package(Assimp REQUIRED)
message("- Assimp Located")
include_directories(${ASSIMP_INCLUDE_DIRS})

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)

configure_file(${PROJECT_SOURCE_DIR}/Util/root_directory.inc.in ${PROJECT_SOURCE_DIR}/Util/root_directory.inc)

file(GLOB SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"

        "${PROJECT_SOURCE_DIR}/Util/*.h"
        "${PROJECT_SOURCE_DIR}/Util/*.cpp"

        "${PROJECT_SOURCE_DIR}/Includes/glad/*.h"
        "${PROJECT_SOURCE_DIR}/Includes/glad/*.c"

        "${PROJECT_SOURCE_DIR}/Includes/glm/*.hpp"
        "${PROJECT_SOURCE_DIR}/Includes/glm/*.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
        ${GLFW_LIBRARIES}
        ${ASSIMP_LIBRARIES}
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/Includes
        ${PROJECT_SOURCE_DIR}
        )