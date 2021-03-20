cmake_minimum_required(VERSION 3.10)

project(NanOptCompare
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

    
    
add_executable(nanopt
    main.cpp
)

add_executable(optoperations
    main_opt.cpp
)


target_link_libraries(nanopt PRIVATE CONAN_PKG::benchmark)
target_link_libraries(optoperations PRIVATE CONAN_PKG::benchmark)
target_compile_options(nanopt PRIVATE -std=c++17)
target_compile_options(optoperations PRIVATE -std=c++17)
