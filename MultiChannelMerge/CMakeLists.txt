add_executable(merge
   main.cpp
   source_generator.cpp
)

target_link_libraries(merge PRIVATE benchmark::benchmark)

