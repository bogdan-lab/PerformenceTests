add_executable(nanopt
    main.cpp
)

add_executable(optoperations
    main_opt.cpp
)


target_link_libraries(nanopt PRIVATE benchmark::benchmark)
target_link_libraries(optoperations PRIVATE benchmark::benchmark)
target_compile_options(nanopt PRIVATE -std=c++17)
target_compile_options(optoperations PRIVATE -std=c++17)
