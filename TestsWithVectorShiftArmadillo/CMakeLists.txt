cmake_minimum_required(VERSION 3.10)

project(ArmadilloShift
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



add_executable(shift_bench
   shift_bench.cpp
)

add_executable(general
    shift_write_get_bench.cpp
    )

target_compile_features(shift_bench PRIVATE cxx_std_17)
target_compile_features(general PRIVATE cxx_std_17)
target_link_libraries(shift_bench PRIVATE CONAN_PKG::benchmark)
target_link_libraries(general PRIVATE CONAN_PKG::benchmark)

