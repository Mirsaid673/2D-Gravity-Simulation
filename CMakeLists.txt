cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME GameEngine)
set(EXECUTABLE out)
set(CXX_STANDARD 11)


set(LIBRARIES GL GLEW glfw)
set(INCLUDE_DIRECTORY ${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "src/*.cpp")
file(GLOB SOURCES "*.cpp" ${SOURCES})
file(GLOB INCLUDE "include/*.h")
file(GLOB INCLUDE "*.h" ${INCLUDE})
file(GLOB LIBS_INCLUDE_DIRECTORY "resource/libs/*")
file(GLOB LIB_SOURCES "resource/libs/*/*.cpp")

include_directories(${INCLUDE_DIRECTORY} ${LIBS_INCLUDE_DIRECTORY})

project(${PROJECT_NAME})

add_executable(${EXECUTABLE} ${SOURCES} ${INCLUDE} ${LIB_SOURCES})
set_target_properties(${EXECUTABLE} PROPERTIES 
	CXX_STANDARD ${CXX_STANDARD})

target_link_libraries(${EXECUTABLE} ${LIBRARIES})