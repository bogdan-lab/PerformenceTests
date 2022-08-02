add_executable(estimate
   main.cpp
)

target_link_libraries(estimate PRIVATE benchmark::benchmark)

