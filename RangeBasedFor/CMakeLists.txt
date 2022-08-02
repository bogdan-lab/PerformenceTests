add_executable(rbf_vec
    main_vec.cpp
)

add_executable(rbf_map
    main_map.cpp
)

add_executable(rbf_deq
    main_deq.cpp
)



target_link_libraries(rbf_vec PRIVATE benchmark::benchmark)
target_link_libraries(rbf_map PRIVATE benchmark::benchmark)
target_link_libraries(rbf_deq PRIVATE benchmark::benchmark)

