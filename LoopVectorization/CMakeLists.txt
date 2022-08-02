#add_subdirectory(dependency)
#add_subdirectory(func_call)
#add_subdirectory(multiple_exits)
#add_subdirectory(complex_flow)
#add_subdirectory(size)
#add_subdirectory(bad_addressing)
#add_subdirectory(diff_stuff)

add_executable(vec_sum vec_sum.cpp)

target_link_libraries(vec_sum PRIVATE benchmark::benchmark)

