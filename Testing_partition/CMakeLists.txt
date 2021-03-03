cmake_minimum_required(VERSION 3.10)

project(Partition
	LANGUAGES CXX)

add_executable(partition
		main.cpp)

set_target_properties(partition PROPERTIES
                      CXX_STANDARD 17
                      CXX_STANDARD_REQUIRED ON)


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


target_link_libraries(partition PRIVATE CONAN_PKG::benchmark)

