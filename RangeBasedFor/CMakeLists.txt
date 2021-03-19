cmake_minimum_required(VERSION 3.10)

project(RangeBasedFor
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

    
    
add_executable(rbf_vec
    main_vec.cpp
)


add_executable(rbf_map
    main_map.cpp
)

add_executable(rbf_deq
    main_deq.cpp
)



target_link_libraries(rbf_vec PRIVATE CONAN_PKG::benchmark)
target_link_libraries(rbf_map PRIVATE CONAN_PKG::benchmark)
target_link_libraries(rbf_deq PRIVATE CONAN_PKG::benchmark)

