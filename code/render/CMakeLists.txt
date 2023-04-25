cmake_minimum_required(VERSION 3.10)
set(ROOT_TARGET ${PROJECT_NAME})
set(TARGET render_opengl)
project(${TARGET} LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(BUILD_DIR ${CMAKE_BINARY_DIR}/${ROOT_TARGET}-${PLATFORM}-${CMAKE_BUILD_TYPE}-${ARCH})
set(CMAKE_BINARY_DIR ${BUILD_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})

message("PLATFORM:         ${PLATFORM}")
message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message("ARCH:             ${ARCH}")
message("COMPILER:         ${CMAKE_C_COMPILER_ID}")

message("CMAKE_SOURCE_DIR:               ${CMAKE_SOURCE_DIR}")
message("CMAKE_BINARY_DIR:               ${CMAKE_BINARY_DIR}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

find_package(SDL2 REQUIRED)
set(FILES
    ${CMAKE_SOURCE_DIR}/vendor/glad/src/glad.c
    render_opengl.h
    render_opengl.c
)
add_library(${TARGET} SHARED ${FILES})
target_include_directories(${TARGET} PRIVATE
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/code
)

# Compiler check
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" AND CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(${TARGET} PRIVATE -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-but-set-parameter)
else()
    if(MSVC)
    	target_compile_options(${TARGET} PRIVATE /W3)
    endif()
endif()

if(WIN32)
    target_link_libraries(${TARGET} PRIVATE )
elseif(LINUX)
    target_link_libraries(${TARGET} PRIVATE ${SDL2_LIBRARIES})
endif()

