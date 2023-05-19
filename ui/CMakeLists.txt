set(TARGET ui)
project(${TARGET})

file(GLOB srcs "*.cpp*")

add_executable(${TARGET} ${srcs} ${hdrs})

target_link_libraries(${TARGET} ${MP_CUSTOM_PROJECT})
