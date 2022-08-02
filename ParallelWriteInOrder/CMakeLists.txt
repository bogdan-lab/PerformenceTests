add_executable(bench_empty
    empty_prints.cpp
)

add_executable(bench_timed
    timed_prints.cpp
)


target_link_libraries(bench_empty PRIVATE benchmark::benchmark)
target_link_libraries(bench_timed PRIVATE benchmark::benchmark)

