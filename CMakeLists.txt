cmake_minimum_required(VERSION 3.10)
project(cpp8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)
set(OpenGL_GL_PREFERENCE LEGACY)

set(CMAKE_CXX_EXTENSIONS ON)
if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    add_compile_options(-fms-extensions)
endif ()
message(STATUS "Build with C++ language extensions")

include_directories(core)
add_subdirectory(core)
add_subdirectory(test)


add_executable(cpp8 Main.cpp)
target_link_libraries(cpp8 core_lib)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(cpp8 ${SDL2_LIBRARY})

if (APPLE)
    SET(CMAKE_EXE_LINKER_FLAGS "-framework Foundation -w")
    target_link_libraries(cpp8 "-framework OpenGL")
endif ()

