cmake_minimum_required(VERSION 3.30...4.0.0)
project(ECSGameEngine)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    include(FetchContent)
    set(SDL_SHARED OFF CACHE BOOL "Build SDL shared library" FORCE)
    set(SDL_STATIC ON CACHE BOOL "Build SDL static library" FORCE)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.0
    )
    FetchContent_MakeAvailable(SDL3)
endif()

find_package(assimp QUIET)
if(NOT assimp_FOUND)
    include(FetchContent)
    set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
    set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)

    FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.4.3
    )
    FetchContent_MakeAvailable(assimp)
endif()

find_package(imgui QUIET)
if(NOT imgui_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.91.6
    )
    FetchContent_MakeAvailable(imgui)

    add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
    )

    target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
    )

    target_link_libraries(imgui PUBLIC SDL3::SDL3)

    add_library(imgui::imgui ALIAS imgui)
endif()

file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
    src/*.c
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(run
    ${ENGINE_SOURCES}
)

target_include_directories(run PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

target_link_libraries(run PRIVATE
    SDL3::SDL3
    assimp::assimp
    imgui::imgui
)

if(WIN32)
    target_link_libraries(run PRIVATE opengl32)
elseif(APPLE)
    find_package(OpenGL REQUIRED)
    target_link_libraries(run PRIVATE OpenGL::GL)
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    find_package(Threads REQUIRED)
    target_link_libraries(run PRIVATE OpenGL::GL)
    target_link_libraries(run PRIVATE Threads::Threads dl)
endif()