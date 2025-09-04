cmake_minimum_required(VERSION 4.1.1)
project(BevyCppClone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)

# EnTT (ECS)
FetchContent_Declare(
    entt
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG v3.15.0 # or latest stable
)

# glm (math)
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

# GLFW (windowing/input)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# bgfx (renderer) - requires bx and bimg
FetchContent_Declare(
    bx
    GIT_REPOSITORY https://github.com/bkaradzic/bx.git
    GIT_TAG master
)

FetchContent_Declare(
    bimg
    GIT_REPOSITORY https://github.com/bkaradzic/bimg.git
    GIT_TAG master
)

FetchContent_Declare(
    bgfx
    GIT_REPOSITORY https://github.com/bkaradzic/bgfx.cmake.git
    GIT_TAG master
)
    
# stb_image (header-only)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
)

# tinygltf
FetchContent_Declare(
    tinygltf
    GIT_REPOSITORY https://github.com/syoyo/tinygltf.git
    GIT_TAG v2.9.6
)

# assimp (models)
FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v6.0.2
)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

# miniaudio (header-only)
FetchContent_Declare(
    miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG 0.11.22
)

FetchContent_MakeAvailable(entt)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(bx)
FetchContent_MakeAvailable(bimg)
FetchContent_MakeAvailable(bgfx)
FetchContent_MakeAvailable(stb)
FetchContent_MakeAvailable(tinygltf)
FetchContent_MakeAvailable(assimp)
FetchContent_MakeAvailable(miniaudio)

# ---- Project Source ----
add_executable(bevycpp
    src/main.cpp
)

target_link_libraries(bevycpp
    PRIVATE
        EnTT::EnTT
        glm
        glfw
        bgfx
        bimg
        bx
        assimp
)

target_include_directories(bevycpp PRIVATE
    ${stb_SOURCE_DIR}
    ${tinygltf_SOURCE_DIR}
    ${miniaudio_SOURCE_DIR}
)
