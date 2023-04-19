cmake_minimum_required(VERSION 3.5)
project(tnt.bin LANGUAGES C)

add_subdirectory(code/modules/render)

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

# ==============================================================================
# Headers and sources
# ==============================================================================

set(FILES
  code/tnt_application.h
  code/tnt_application.c
  code/tnt_types.h
  code/tnt_linked_list.h
  code/tnt_linked_list.c
  code/tnt_logger.h
  code/tnt_os.h
  code/tnt_os.c
  code/tnt_render.h
  code/tnt_render.c
  code/tnt_string.h
  code/tnt_math.h
  code/tnt_math.c
  code/tnt_camera.h
  code/tnt_camera.c
  code/tnt_memory_arena.h
  code/tnt_memory_arena.c
  code/tnt_ui.h
  code/tnt_ui.c
  code/tnt_net.h
  code/tnt_net.c
)

# ==============================================================================
# Target definition
# ==============================================================================

set(TARGET tnt.bin)
add_executable(${TARGET} ${FILES})

# ==============================================================================
# Vendor 
# ==============================================================================

find_package(SDL2 REQUIRED)

# ==============================================================================
# External
# ==============================================================================

target_include_directories(${TARGET} PRIVATE 
    ${PROJECT_SOURCE_DIR}/code
    ${PROJECT_SOURCE_DIR}/vendor/glad/include
    ${PROJECT_SOURCE_DIR}/vendor/cglm-0.8.9/include
  	${SDL2_INCLUDE_DIR}
)
target_link_libraries(${TARGET} PRIVATE -Wl,--export-dynamic)

# ==============================================================================
# Target properties
# ==============================================================================

set_target_properties(${TARGET} PROPERTIES C_STANDARD 11)
set_target_properties(${TARGET} PROPERTIES C_EXTENSIONS ON)

# ==============================================================================
# Compile options
# ==============================================================================

if(MSVC)
    target_compile_options(${TARGET} PRIVATE /W3 /D_CRT_SECURE_NO_WARNINGS)
    target_compile_options(${TARGET} PRIVATE /fp:fast)
else()
    target_compile_options(${TARGET} PRIVATE -O0 -g -DENABLE_ASSERT -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-but-set-parameter)
endif()

# ==============================================================================
# Link libraries
# ==============================================================================

if(WIN32)
    target_link_libraries(${TARGET} PRIVATE )
elseif(LINUX)
    target_link_libraries(${TARGET} PRIVATE m dl X11 ${SDL2_LIBRARIES})
endif()

# ==============================================================================
# Asset files
# ==============================================================================

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
    COMMAND ${CMAKE_COMMAND} -E echo
    "${ASSETS_MSG}: ${ASSETS_SRC} to ${ASSETS_DST}"
)
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E ${ASSETS_CMD}
    "${ASSETS_SRC}" "${ASSETS_DST}"
)
