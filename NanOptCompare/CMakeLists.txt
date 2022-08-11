generate_target_name(nan_check "nan")
add_executable(${nan_check}
    main.cpp
)

generate_target_name(operation_check "op")
add_executable(${operation_check}
    main_opt.cpp
)


target_link_libraries(${nan_check} PRIVATE benchmark::benchmark)
target_link_libraries(${operation_check} PRIVATE benchmark::benchmark)
target_compile_options(${nan_check} PRIVATE -std=c++17)
target_compile_options(${operation_check} PRIVATE -std=c++17)
