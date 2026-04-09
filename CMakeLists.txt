cmake_minimum_required(VERSION 4.0.2)

# CMake < 3.5 compatibility for Raylib
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(eomm_snake)

# --- 1. Raylib Setup ---
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(raylib)

# --- 2. Project Files ---
file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 3. THE "PREDICTABLE PATH" ---
# This forces the .exe to always go to build/bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# These lines ensure that Multi-Config generators (like Visual Studio)
# don't add their own /Debug or /Release subfolders.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG   ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)

# --- 4. Include & Link ---
target_include_directories(${PROJECT_NAME} PRIVATE "include" "src")
target_link_libraries(${PROJECT_NAME} raylib)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
elseif(LINUX)
    target_link_libraries(${PROJECT_NAME} X11 GL m pthread dl rt)
endif()

# --- 5. Resource Sync ---
# This copies your 'resources' folder into 'build/bin/resources'
# so the game can actually find your assets when run.
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/resources"
        COMMENT "Syncing resources to bin folder..."
)