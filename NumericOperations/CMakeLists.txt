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



add_executable(num_ops
    main.cpp
)

target_compile_features(num_ops PRIVATE cxx_std_17)
target_link_libraries(num_ops PRIVATE CONAN_PKG::benchmark)
target_compile_options(num_ops PRIVATE -Wall -Werror -Wpedantic -fno-omit-frame-pointer)
