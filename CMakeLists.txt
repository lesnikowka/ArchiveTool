cmake_minimum_required(VERSION 3.25)

set(PROJECT_NAME ArchiveTool)

project(${PROJECT_NAME})

set(MP_CUSTOM_PROJECT "${PROJECT_NAME}")

set(MP_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(MP_UI "${CMAKE_CURRENT_SOURCE_DIR}/ui")
set(MP_SAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/samples")

add_subdirectory(ui)
add_subdirectory(samples)
add_subdirectory(include)
add_subdirectory(bitset)