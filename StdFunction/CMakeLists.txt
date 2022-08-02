add_executable(callback_test
        outside_less.h
        outside_less.cpp
		main.cpp)

set_target_properties(callback_test PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)

target_link_libraries(callback_test PRIVATE benchmark::benchmark)

