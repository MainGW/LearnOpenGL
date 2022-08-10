cmake_minimum_required(VERSION 3.10)
project(OpenGL_Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Og -Wall -g -ggdb")

aux_source_directory(src SOURCES_FILE)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED IMPORTED_TARGET glfw3)

include_directories(include
    ${OPENGL_INCLUDE_DIRS}
    ${GLFW_INCLUDE_DIRS}    
)

add_executable(${PROJECT_NAME} ${SOURCES_FILE})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} PkgConfig::GLFW)

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/rsrc ${CMAKE_CURRENT_BINARY_DIR}/rsrc )

