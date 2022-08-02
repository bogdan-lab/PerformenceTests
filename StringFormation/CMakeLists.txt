add_executable(string_formation
    main.cpp
)


target_compile_features(string_formation PRIVATE cxx_std_17)
target_link_libraries(string_formation PRIVATE benchmark::benchmark)

