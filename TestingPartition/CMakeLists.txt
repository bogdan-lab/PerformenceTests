add_executable(partition
		main.cpp)

set_target_properties(partition PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)


target_link_libraries(partition PRIVATE benchmark::benchmark)

