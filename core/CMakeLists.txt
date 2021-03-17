project(core)

set(ENGINE_FILES
        Chip8.cpp Chip8.h Keyboard.cpp Keyboard.h Registers.cpp Registers.h Display.cpp Display.h Memory.cpp Memory.h)

add_library(core_lib STATIC ${ENGINE_FILES})

if (NOT EMSCRIPTEN)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    target_link_libraries(core_lib ${SDL2_LIBRARY})
else ()
    set(USE_FLAGS "-s USE_SDL=2 -s USE_SDL_MIXER=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS} -Wno-c++11-narrowing")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX .html)
endif ()

target_link_libraries(core_lib)