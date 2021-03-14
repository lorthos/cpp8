project(test)

add_executable(
        run_tests
        catch.hpp
        test1.cpp)

target_link_libraries(run_tests core_lib)
