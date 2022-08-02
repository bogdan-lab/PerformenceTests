cmake_minimum_required(VERSION 3.10)

project(MultiChannelMerge
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



add_executable(test
   main.cpp
   source_generator.cpp
)


target_link_libraries(test PRIVATE CONAN_PKG::benchmark)

