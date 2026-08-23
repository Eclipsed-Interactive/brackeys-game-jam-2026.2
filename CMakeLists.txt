cmake_minimum_required(VERSION 3.19.2)

set(GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Project")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

set(PROJECT_DIR "${PROJECT_DIR}" CACHE PATH "Where to place executables")
set(ENGINE_PATH "${ENGINE_PATH}" CACHE PATH "Where to place executables")

project(Eclipsed-Game LANGUAGES CXX)

option(BUILD_GAME "Build game as static library." OFF)
option(ECLIPSED_EDITOR "Build game as static library." OFF)

set(CONFIG "Debug" CACHE STRING "Game build path")

option(ENABLE_NETWORKING "Includes the network engine in game build." ON)
if(${ENABLE_NETWORKING})
    add_compile_definitions(ECLIPSED_NETWORKING)
endif()

option(ENABLE_STEAM_SDK "Enables the steam sdk." ON)
if(${ENABLE_STEAM_SDK})
    add_compile_definitions(ENABLE_STEAM_SDK)
endif()

option(ENABLE_DISCORD_SDK "Enables the discord sdk." ON)
if(${ENABLE_DISCORD_SDK})
    add_compile_definitions(ENABLE_DISCORD_SDK)
endif()

file(GLOB_RECURSE GAME_SOURCES
    "${GAME_ROOT}/*.cpp"
    "${GAME_ROOT}/*.h"
    "${GAME_ROOT}/*.c"
    "${GAME_ROOT}/*.hpp"
    "${GAME_ROOT}/*.ipp"
    "${GAME_ROOT}/*.inl"
)

if(${ECLIPSED_EDITOR})
    add_library(Game SHARED ${GAME_SOURCES})
    add_compile_definitions(
        ECLIPSED_EDITOR
        _ECLIPSED_GAME_EXPORT_DLL
    )
else()
    add_library(Game STATIC ${GAME_SOURCES})
endif()

target_include_directories(Game PUBLIC ${GAME_ROOT})

target_link_options(Game PRIVATE /OPT:NOREF /OPT:NOICF)

set_target_properties(Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Temp"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/Temp"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/Temp"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_CURRENT_SOURCE_DIR}/Temp"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_CURRENT_SOURCE_DIR}/Temp"
)

set(DIR "")

if(NOT DEFINED ENGINE_PATH OR "${ENGINE_PATH}" STREQUAL "")
    set(DIR "${CMAKE_SOURCE_DIR}")
else()
    set(DIR "${ENGINE_PATH}")
endif()

message(STATUS "CONFIG: ${CONFIG}")
message(STATUS "ENGINE_PATH: ${DIR}")

function(LINK_GAME_LIBRARIES)
    target_include_directories(Game PRIVATE 
        ${DIR}/Source/Engine/EclipsedEngine
        ${DIR}/Source/Engine/Modules/AssetEngine
        ${DIR}/Source/Engine/Modules/GraphicsEngine
        ${DIR}/Source/Engine/Modules/PhysicsEngine
        ${DIR}/Source/Engine/Modules/NetworkEngine
        ${DIR}/Source/Externals
    )
endfunction()

function(LINK_EDITOR_LIBRARIES)
    target_include_directories(Game PRIVATE
        ${DIR}/Source/Engine/EclipsedEngine
        ${DIR}/Source/Engine/Modules/CoreEngine
        ${DIR}/Source/Engine/Modules/AssetEngine
        ${DIR}/Source/Engine/Modules/GraphicsEngine
        ${DIR}/Source/Engine/Modules/PhysicsEngine
        ${DIR}/Source/Engine/Modules/NetworkEngine 
        ${DIR}/Source/Externals/steamsdk 
        ${DIR}/Source/Externals/DiscordSDK 
        ${DIR}/Source/Externals
    )
endfunction()

if(${ECLIPSED_EDITOR})
    LINK_EDITOR_LIBRARIES()
else()
    LINK_GAME_LIBRARIES()
endif()

list(APPEND CMAKE_PREFIX_PATH "${ENGINE_PATH}/Temp/Install")

# Remove this find_package - it's not needed since we're linking directly
find_package(EntityEngine REQUIRED)
target_link_libraries(Game PRIVATE
    Eclipsed::EntityEngine
)