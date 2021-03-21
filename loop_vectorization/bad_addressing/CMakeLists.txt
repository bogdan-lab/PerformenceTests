add_executable(p6_addressing
		addres.cpp
)

target_link_libraries(p6_addressing PRIVATE CONAN_PKG::benchmark)

