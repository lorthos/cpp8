project(test)

add_executable(
        run_tests
        catch.hpp
        test_basic_state.cpp test_load_rom.cpp test_run_instruction.cpp)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(run_tests core_lib)
