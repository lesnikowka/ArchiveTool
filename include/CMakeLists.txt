set(TARGET ${MP_CUSTOM_PROJECT})
project(${TARGET})

file(GLOB hdrs "*.h*")

add_custom_target(${TARGET} SOURCES ${hdrs})
