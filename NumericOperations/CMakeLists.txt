add_executable(num_ops_in_vec
    main_vec.cpp
)

target_compile_features(num_ops_in_vec PRIVATE cxx_std_17)
target_link_libraries(num_ops_in_vec PRIVATE benchmark::benchmark)



add_executable( num_ops_bare
    main_bare.cpp
)

target_compile_features(num_ops_bare PRIVATE cxx_std_17)
target_link_libraries(num_ops_bare PRIVATE benchmark::benchmark)

