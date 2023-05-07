set(TARGET ui)
project(${TARGET})

file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp*")

add_executable(${TARGET} ${srcs} ${hdrs})

target_include_directories(${TARGET} PUBLIC ${MP_INCLUDE})
