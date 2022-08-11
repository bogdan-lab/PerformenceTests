cmake_minimum_required(VERSION 3.10)

project(PerformanceTests LANGUAGES CXX)

function(generate_target_name output prefix)    
    get_filename_component(dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    string(TOLOWER ${dir_name} dir_name)
    string(CONCAT tmp ${prefix} "_" ${dir_name})
    set(${output} ${tmp} PARENT_SCOPE)
endfunction()

find_package(benchmark REQUIRED)

add_subdirectory(MultiChannelMerge)
add_subdirectory(2DArrFill)
add_subdirectory(LoopVectorization)
add_subdirectory(EstimateMapDestructor)
add_subdirectory(MethodThroughAccess)
add_subdirectory(NanOptCompare)
add_subdirectory(NumericOperations)
add_subdirectory(ParallelWriteInOrder)
add_subdirectory(RangeBasedFor)
add_subdirectory(StdFunction)
add_subdirectory(StringFormation)
add_subdirectory(TryCatchTest)
add_subdirectory(TestingPartition)
add_subdirectory(TestsWithVectorShiftArmadillo)

