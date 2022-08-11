generate_target_name(vector_test "vec_test")
add_executable(vector_test
    main_vec.cpp
)

target_compile_features(vector_test PRIVATE cxx_std_17)
target_link_libraries(vector_test PRIVATE benchmark::benchmark)


generate_target_name(bare_test "bare_test")
add_executable(${bare_test}
    main_bare.cpp
)

target_compile_features(${bare_test} PRIVATE cxx_std_17)
target_link_libraries(${bare_test} PRIVATE benchmark::benchmark)

