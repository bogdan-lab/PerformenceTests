﻿cmake_minimum_required(VERSION 3.10)

project(LoopVectorization
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

    
    
add_executable(problem_1
		data_dependency.cpp
        data_dependency_bench.cpp)

target_link_libraries(problem_1 PRIVATE CONAN_PKG::benchmark)

