add_executable(p4_complex_flow
		comp_flow.cpp
)

target_link_libraries(p4_complex_flow PRIVATE CONAN_PKG::benchmark)

