add_executable(p5_size
		size.cpp
)

target_link_libraries(p5_size PRIVATE CONAN_PKG::benchmark)

