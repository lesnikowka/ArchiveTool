set(TARGET ${MP_CUSTOM_PROJECT})

project(${TARGET})

file(GLOB srcs "*.h*")


include_directories(${MP_ALGORITHM})
include_directories(${MP_FILE})

add_custom_target(${TARGET} SOURCES ${srcs})

