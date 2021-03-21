add_executable(p3_mult_ex
		mult_exits.cpp
)

target_link_libraries(p3_mult_ex PRIVATE CONAN_PKG::benchmark)

