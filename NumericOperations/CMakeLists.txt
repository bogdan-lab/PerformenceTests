cmake_minimum_required(VERSION 3.10)

project(NumericOperations
	LANGUAGES CXX)


#CONAN
find_program(CONAN conan)
if (NOT CONAN)
    message(FATAL_ERROR "Needs conan package manager: please visit https://conan.io and install")
endif ()
include(../cmake/conan.cmake)
conan_check(VERSION 1.14.4 REQUIRED)
conan_cmake_run(REQUIRES
                benchmark/1.5.2
        OPTIONS BASIC_SETUP CMAKE_TARGETS
        BUILD missing)



add_executable(num_ops_in_vec
    main_vec.cpp
)

target_compile_features(num_ops_in_vec PRIVATE cxx_std_17)
target_link_libraries(num_ops_in_vec PRIVATE CONAN_PKG::benchmark)
#target_compile_options(num_ops_in_vec PRIVATE -Wall -Werror -Wpedantic -fno-omit-frame-pointer)



add_executable( num_ops_bare
    main_bare.cpp
)

target_compile_features(num_ops_bare PRIVATE cxx_std_17)
target_link_libraries(num_ops_bare PRIVATE CONAN_PKG::benchmark)
#target_compile_options(num_ops_bare PRIVATE -Wall -Werror -Wpedantic -fno-omit-frame-pointer)

