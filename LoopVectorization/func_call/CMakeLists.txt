add_executable(p2_func_call
		func_call.cpp
)

target_link_libraries(p2_func_call PRIVATE CONAN_PKG::benchmark)

