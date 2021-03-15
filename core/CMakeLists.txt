project(core)

set(ENGINE_FILES
        Chip8.cpp Chip8.h)

add_library(core_lib STATIC ${ENGINE_FILES})

target_link_libraries(core_lib)