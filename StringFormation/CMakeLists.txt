generate_target_name(target_name "out")
add_executable(${target_name}
    main.cpp
)


target_compile_features(${target_name} PRIVATE cxx_std_17)
target_link_libraries(${target_name} PRIVATE benchmark::benchmark)

