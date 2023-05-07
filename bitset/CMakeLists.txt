set(TARGET bitset)
project(${TARGET})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp*")

add_custom_target(${TARGET} SOURCES ${hdrs} ${srcs})
