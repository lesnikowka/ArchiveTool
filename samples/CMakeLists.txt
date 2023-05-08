set(TARGET samples)
project(${TARGET})

file(GLOB srcs "*.cpp*")

add_executable(${TARGET} ${srcs})

target_link_libraries(${TARGET} ${MP_CUSTOM_PROJECT})

