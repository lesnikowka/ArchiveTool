set(TARGET ${MP_CUSTOM_PROJECT})

project(${TARGET})

file(GLOB srcs "*.h*")


include_directories(${MP_ALGORITHM})
include_directories(${MP_FILE})
include_directories(${MP_THREAD_POOL})

add_custom_target(${TARGET} SOURCES ${srcs})