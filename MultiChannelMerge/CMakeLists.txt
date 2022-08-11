generate_target_name(target_name "out")
add_executable(${target_name}
   main.cpp
   source_generator.cpp
)

target_link_libraries(${target_name} PRIVATE benchmark::benchmark)

