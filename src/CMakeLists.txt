set(TARGET ${MP_CUSTOM_PROJECT})
project(${TARGET})

file(GLOB hdrs "${MP_INCLUDE}/*.h*")
file(GLOB srcs "*.cpp*")

add_library(${TARGET} STATIC ${hdrs} ${srcs})

