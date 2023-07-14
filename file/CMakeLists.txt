set(TARGET file)

project(${TARGET})

file(GLOB srcs "*.h*")

include_directories(MP_BITFIELD)

add_custom_target(${TARGET} SOURCES ${srcs})


