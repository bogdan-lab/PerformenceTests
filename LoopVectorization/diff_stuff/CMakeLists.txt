add_executable(p7_different_stuff
		diff_stuff.cpp
)

target_link_libraries(p7_different_stuff PRIVATE CONAN_PKG::benchmark)

