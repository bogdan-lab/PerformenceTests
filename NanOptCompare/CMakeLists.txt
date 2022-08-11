create_benchmark(nan_check "nan" main.cpp)
create_benchmark(operation_check "op" main_opt.cpp)

target_compile_features(${nan_check} PRIVATE cxx_std_17)
target_compile_features(${operation_check} PRIVATE cxx_std_17)
