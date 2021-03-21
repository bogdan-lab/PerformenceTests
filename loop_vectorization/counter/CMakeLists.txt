add_executable(p2_dependency
		counter.cpp
        counter_bench.cpp)

target_link_libraries(p2_dependency PRIVATE CONAN_PKG::benchmark)

