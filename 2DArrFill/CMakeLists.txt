cmake_minimum_required(VERSION 3.10)

project(2DArrFill
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

    

add_executable(fill_2Darr
    main.cpp
)

add_executable(access
    access.cpp
)


target_link_libraries(fill_2Darr PRIVATE CONAN_PKG::benchmark)
target_link_libraries(access PRIVATE CONAN_PKG::benchmark)

