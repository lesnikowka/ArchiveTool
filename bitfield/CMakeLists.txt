set(TARGET bitfield)

project(${TARGET})

file(GLOB srcs "*.h*")

add_custom_target(${TARGET} SOURCES ${srcs})



