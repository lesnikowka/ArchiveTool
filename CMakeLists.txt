cmake_minimum_required(VERSION 3.22.1)

set(PROJECT_NAME ArchiveTool)

set(CMAKE_CXX_STANDARD 14)

project(${PROJECT_NAME})

set(MP_CUSTOM_PROJECT "${PROJECT_NAME}")

set(MP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MP_UI "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(MP_SAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/samples")
set(MP_BITFIELD "${CMAKE_CURRENT_SOURCE_DIR}/bitfield")
set(MP_ALGORITHM "${CMAKE_CURRENT_SOURCE_DIR}/algorithm")
set(MP_FILE "${CMAKE_CURRENT_SOURCE_DIR}/file")

include_directories(include)
include_directories(ui)
include_directories(file)
include_directories(algorithm)
include_directories(samples)
include_directories(bitfield)


add_subdirectory(bitfield)
add_subdirectory(file)
add_subdirectory(algorithm)
add_subdirectory(include)
add_subdirectory(ui)
add_subdirectory(samples)
