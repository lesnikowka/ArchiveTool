set(TARGET samples)
project(${TARGET})

file(GLOB srcs "*.cpp*")

add_executable(${TARGET} ${srcs})

target_include_directories(${TARGET} PUBLIC ${MP_INCLUDE})

