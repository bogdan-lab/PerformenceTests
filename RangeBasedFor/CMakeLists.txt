generate_target_name(vec_case "vec")
add_executable(${vec_case}
    main_vec.cpp
)

generate_target_name(map_case "map")
add_executable(${map_case}
    main_map.cpp
)

generate_target_name(deq_case "deq")
add_executable(${deq_case}
    main_deq.cpp
)



target_link_libraries(${vec_case} PRIVATE benchmark::benchmark)
target_link_libraries(${map_case} PRIVATE benchmark::benchmark)
target_link_libraries(${deq_case} PRIVATE benchmark::benchmark)

