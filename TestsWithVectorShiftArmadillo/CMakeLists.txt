generate_target_name(shift "shift")
add_executable(${shift}
   shift_bench.cpp
)

generate_target_name(rotate "rotate")
add_executable(${rotate}
    rotate_bench.cpp
)

generate_target_name(general "general")
add_executable(${general}
    shift_write_get_bench.cpp
)

target_link_libraries(${shift} PRIVATE benchmark::benchmark)
target_link_libraries(${rotate} PRIVATE benchmark::benchmark)
target_link_libraries(${general} PRIVATE benchmark::benchmark)

