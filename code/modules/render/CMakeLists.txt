cmake_minimum_required(VERSION 3.5)
project(render_opengl LANGUAGES C)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

message("CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")

if(LINUX)
    set(CMAKE_C_COMPILER "/usr/bin/clang")
    set(CMAKE_CXX_COMPILER "/usr/bin/clang++")
endif()

message("CMAKE_BUILD_TYPE:   ${CMAKE_BUILD_TYPE}")
message("CMAKE_C_COMPILER:   ${CMAKE_C_COMPILER}")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message("Setting build type to 'Debug' as none was specified.")

  set(CMAKE_BUILD_TYPE Debug)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

set(TARGET ${PROJECT_NAME})
add_library(${TARGET} SHARED
  ${ROOT_DIR}/vendor/glad/src/glad.c
  render_opengl.h
  render_opengl.c
)
target_include_directories(${TARGET} PRIVATE
    ${ROOT_DIR}/vendor/glad/include
    ${ROOT_DIR}/code
    ${PROJECT_SOURCE_DIR}
)

find_package(SDL2 REQUIRED)

set_target_properties(${TARGET} PROPERTIES C_STANDARD 11)
set_target_properties(${TARGET} PROPERTIES C_EXTENSIONS ON)

set_target_properties(${TARGET}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

if(MSVC)
    target_compile_options(${TARGET} PRIVATE /W3 /D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(${TARGET} PRIVATE /fp:fast)
else()
    target_compile_options(${TARGET} PRIVATE -O0 -g -DENABLE_ASSERT -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-but-set-parameter)
endif()

target_link_libraries(${TARGET} PRIVATE ${SDL2_LIBRARIES})
