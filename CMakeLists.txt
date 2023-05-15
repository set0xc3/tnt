cmake_minimum_required(VERSION 3.10)
set(TARGET tnt)
project(${TARGET} LANGUAGES C)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Set the platform
if(NOT DEFINED PLATFORM)
    message(FATAL_ERROR "MY_PARAMETER is not defined")
endif()

# Set the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE debug)
endif()

# Set the architecture
if(NOT DEFINED ARCH)
    set(ARCH "x32")
endif()

set(BUILD_DIR ${CMAKE_BINARY_DIR}/${TARGET}-${PLATFORM}-${CMAKE_BUILD_TYPE}-${ARCH})
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
	code/tnt_app.c
	code/tnt_linked_list.c
	code/tnt_os.c
	code/tnt_render.c
	code/tnt_math.c
	code/tnt_camera.c
	code/tnt_memory_arena.c
	code/tnt_ui.c
	code/tnt_thread.c
	code/tnt_scene.c
    code/tnt_game.c
)
add_executable(${TARGET} ${FILES})
target_include_directories(${TARGET} PRIVATE
    ${SDL2_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/vendor/glad/include
    ${CMAKE_SOURCE_DIR}/code
)
# target_link_libraries(${TARGET} PRIVATE -Wl,-rpath,${CMAKE_BINARY_DIR}/mylib-${PLATFORM}-${CMAKE_BUILD_TYPE}-${ARCH})
target_link_libraries(${TARGET} PRIVATE -Wl,--export-dynamic)
set_property(TARGET ${TARGET} PROPERTY C_STANDARD 99)

add_custom_target(run
    COMMAND cd ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} && ./${TARGET} ${ARGS}
)

# Compiler check
if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
		target_compile_options(${TARGET} PRIVATE -DENABLE_ASSERT -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-but-set-parameter)
else()
    if(MSVC)
    	target_compile_options(${TARGET} PRIVATE /DENABLE_ASSERT /W3)
    endif()
endif()

if(WIN32)
    target_link_libraries(${TARGET} PRIVATE )
elseif(LINUX)
    target_link_libraries(${TARGET} PRIVATE m dl X11 ${SDL2_LIBRARIES} uuid)
endif()


# Asset files
set(ASSETS_SRC "${CMAKE_SOURCE_DIR}/assets")
set(ASSETS_DST "$<TARGET_FILE_DIR:${TARGET}>/assets")

if(WIN32)
    set(ASSETS_CMD copy_directory)
    set(ASSETS_MSG "Copy assets")
else()
    set(ASSETS_CMD create_symlink)
    set(ASSETS_MSG "Link assets")
endif()

add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "${ASSETS_MSG}: ${ASSETS_SRC} to ${ASSETS_DST}"
    COMMAND ${CMAKE_COMMAND} -E ${ASSETS_CMD} "${ASSETS_SRC}" "${ASSETS_DST}"
)
