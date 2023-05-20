set(TARGET ui)
project(${TARGET})

file(GLOB srcs "*.cpp*")
file(GLOB hdrs "*.h*")

add_executable(${TARGET} ${srcs} ${hdrs})

target_link_libraries(${TARGET} ${MP_CUSTOM_PROJECT})
