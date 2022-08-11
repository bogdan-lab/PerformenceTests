generate_target_name(fill_target_name "fill")
add_executable(${fill_target_name}
    main.cpp
)

generate_target_name(access_target_name "access")
add_executable(${access_target_name}
    access.cpp
)

target_link_libraries(${fill_target_name} PRIVATE benchmark::benchmark)
target_link_libraries(${access_target_name} PRIVATE benchmark::benchmark)
