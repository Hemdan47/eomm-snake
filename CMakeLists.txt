cmake_minimum_required(VERSION 4.0.2)

# 1. Compatibility for Raylib on modern CMake versions
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(eomm_snake)

# --- RAYLIB SETUP (Automatic Download) ---
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)

# Configure raylib to build quietly and efficiently
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# --- PROJECT SETUP ---

# Automatically find all .cpp files in the src folder
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

# --- OUTPUT DIRECTORY ---
# This ensures the .exe and resources land in build/bin/
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin")

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}"
)

# --- INCLUDE & LINKING ---

# Search for your headers in 'include' and 'src'
target_include_directories(${PROJECT_NAME} PRIVATE "include" "src")

# Link Raylib (automatically handles its headers and libraries)
target_link_libraries(${PROJECT_NAME} raylib)

# Link OS-specific system libraries
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(LINUX)
    target_link_libraries(${PROJECT_NAME} X11 GL m pthread dl rt)
endif()

# --- RESOURCE SYNC ---
# This copies your 'resources' folder into 'build/bin/resources'
# so your LoadTexture() calls don't fail when running the .exe.
if(EXISTS "${CMAKE_SOURCE_DIR}/resources")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/resources"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
            COMMENT "Syncing resources to the bin folder..."
    )
endif()