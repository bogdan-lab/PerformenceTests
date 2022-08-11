create_benchmark(target_name "out" main.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)
