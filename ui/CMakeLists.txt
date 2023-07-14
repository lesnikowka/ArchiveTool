set(TARGET ui)
project(${TARGET})

file(GLOB srcs "*.cpp*" "*.h*")

add_executable(${TARGET} ${srcs})

target_include_directories(${TARGET} PUBLIC ${MP_INCLUDE})
