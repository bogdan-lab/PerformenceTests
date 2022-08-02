add_executable(access_BM
    main.cpp
    level_1.cpp
)

target_link_libraries(access_BM PRIVATE benchmark::benchmark)

