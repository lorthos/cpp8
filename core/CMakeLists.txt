project(core)

set(ENGINE_FILES
        Chip8.cpp Chip8.h Keyboard.cpp Keyboard.h)

add_library(core_lib STATIC ${ENGINE_FILES})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(core_lib ${SDL2_LIBRARY})

target_link_libraries(core_lib)