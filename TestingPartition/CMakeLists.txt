generate_target_name(target_name "out")
add_executable(${target_name}
		main.cpp)

set_target_properties(${target_name} PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)


target_link_libraries(${target_name} PRIVATE benchmark::benchmark)

