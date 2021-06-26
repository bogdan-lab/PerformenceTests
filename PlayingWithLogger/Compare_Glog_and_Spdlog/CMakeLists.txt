cmake_minimum_required(VERSION 3.10)

project(CompareGlogSpdlog
    LANGUAGES CXX)



#CONAN
find_program(CONAN conan)
if (NOT CONAN)
    message(FATAL_ERROR "Needs conan package manager: please visit https://conan.io and install")
endif ()
include(../../cmake/conan.cmake)
conan_check(VERSION 1.33.0 REQUIRED)
conan_cmake_run(REQUIRES
                glog/0.4.0
                spdlog/1.8.5
        OPTIONS BASIC_SETUP CMAKE_TARGETS
        BUILD missing)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

qt5_wrap_cpp(SRC log_widget.h)


add_executable(CompareGlogSpdlog main.cpp ${SRC})

target_link_libraries(CompareGlogSpdlog PRIVATE Qt5::Widgets pthread CONAN_PKG::glog CONAN_PKG::spdlog)
