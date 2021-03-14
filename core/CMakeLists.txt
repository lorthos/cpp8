project(core)

set(ENGINE_FILES
        GameMath.cpp
        GameMath.h
        )

add_library(core_lib STATIC ${ENGINE_FILES})

target_link_libraries(core_lib)