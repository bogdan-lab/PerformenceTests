#add_subdirectory(dependency)
#add_subdirectory(func_call)
#add_subdirectory(multiple_exits)
#add_subdirectory(complex_flow)
#add_subdirectory(size)
#add_subdirectory(bad_addressing)
#add_subdirectory(diff_stuff)

generate_target_name(target_name "out")
add_executable(${target_name} vec_sum.cpp)

target_link_libraries(${target_name} PRIVATE benchmark::benchmark)

