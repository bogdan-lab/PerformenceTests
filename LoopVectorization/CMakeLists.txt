#add_subdirectory(dependency)
#add_subdirectory(func_call)
#add_subdirectory(multiple_exits)
#add_subdirectory(complex_flow)
#add_subdirectory(size)
#add_subdirectory(bad_addressing)
#add_subdirectory(diff_stuff)

create_benchmark(target_name "out" vec_sum.cpp)
