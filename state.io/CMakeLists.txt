cmake_minimum_required(VERSION 3.16)
project("Sample SDL project")
include_directories("/usr/include/SDL2")
include_directories("include")

file(GLOB_RECURSE SOURCE "src/*.c" )
add_executable(main "${SOURCE}")

target_link_libraries(main m SDL2 SDL2_gfx SDL2_ttf)