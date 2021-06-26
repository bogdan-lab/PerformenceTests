cmake_minimum_required(VERSION 3.10)

project(PlayingWithLogger
	LANGUAGES CXX)

    
    
add_executable(loggs
    main.cpp
)

target_link_libraries( loggs PRIVATE -lpthread)
target_compile_options(loggs PRIVATE -Wall -Wextra -Wpedantic -Werror)
