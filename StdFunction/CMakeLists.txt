create_benchmark(target_name "out" outside_less.h
                                    outside_less.cpp
                            		main.cpp)
target_compile_features(${target_name} PRIVATE cxx_std_17)