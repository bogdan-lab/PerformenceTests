add_executable(p1_dependency
		data_dependency.cpp
        data_dependency_bench.cpp)

target_link_libraries(p1_dependency PRIVATE CONAN_PKG::benchmark)

