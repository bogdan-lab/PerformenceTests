create_benchmark(vector_test "vec_test" main_vec.cpp)
target_compile_features(${vector_test} PRIVATE cxx_std_17)

create_benchmark(bare_test "bare_test" main_bare.cpp)
target_compile_features(${bare_test} PRIVATE cxx_std_17)

