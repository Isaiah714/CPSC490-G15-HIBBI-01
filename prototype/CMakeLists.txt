cmake_minimum_required(VERSION 3.30...4.0.0)
project(ECSGameEngine)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


find_package(SDL3 REQUIRED)

find_package(assimp REQUIRED)

find_package(glm REQUIRED)

add_executable(run
    src/main.cpp
    src/glad.c
    lib/include/stb_image/stb_image.cpp
)

target_include_directories(run PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/include
)

target_link_libraries(run PRIVATE
    SDL3::SDL3
    assimp::assimp
    glm::glm
)

if(WIN32)
    target_link_libraries(run PRIVATE opengl32)

    # Optional: Copy DLLs or handle Windows subsystems if needed (e.g., hide console in Release)
    # set_target_properties(run PROPERTIES WIN32_EXECUTABLE TRUE)

elseif(UNIX AND NOT APPLE)
    find_package(OpenGL REQUIRED)
    find_package(Threads REQUIRED)
    target_link_libraries(run PRIVATE OpenGL::GL)
    
    target_link_libraries(run PRIVATE Threads::Threads dl)
endif()

