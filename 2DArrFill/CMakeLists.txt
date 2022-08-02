
add_executable(fill_2Darr
    main.cpp
)

add_executable(access
    access.cpp
)


target_link_libraries(fill_2Darr PRIVATE benchmark::benchmark)
target_link_libraries(access PRIVATE benchmark::benchmark)

