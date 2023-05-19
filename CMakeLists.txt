cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME ArchiveTool)

set(CMAKE_CXX_STANDARD 14)

project(${PROJECT_NAME})

set(MP_CUSTOM_PROJECT "${PROJECT_NAME}")

set(MP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MP_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(MP_UI "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(MP_SAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/samples")

include_directories(${MP_INCLUDE})

add_subdirectory(src)
add_subdirectory(ui)
add_subdirectory(samples)