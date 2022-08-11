generate_target_name(empty "empty")
add_executable(${empty}
    empty_prints.cpp
)

generate_target_name(timed "timed")
add_executable(${timed}
    timed_prints.cpp
)


target_link_libraries(${empty} PRIVATE benchmark::benchmark)
target_link_libraries(${timed} PRIVATE benchmark::benchmark)

