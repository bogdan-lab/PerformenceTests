
add_executable(shift_bench
   shift_bench.cpp
)

add_executable(rotate_bench
    rotate_bench.cpp
)

add_executable(general
    shift_write_get_bench.cpp
)

target_compile_options( general PRIVATE -fno-omit-frame-pointer)

target_link_libraries(shift_bench PRIVATE benchmark::benchmark)
target_link_libraries(rotate_bench PRIVATE benchmark::benchmark)
target_link_libraries(general PRIVATE benchmark::benchmark)

