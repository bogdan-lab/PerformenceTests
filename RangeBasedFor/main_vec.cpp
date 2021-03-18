#include "benchmark/benchmark.h"
#include <algorithm>
#include <random>
#include <string>

#define ELEMENT_NUM 10000
#define STRING_LEN 257

std::mt19937 rnd(42);

std::string get_random_string(size_t num){
    std::uniform_int_distribution<uint8_t> char_dist(0, 255);
    std::string str;
    str.reserve(num);
    for(size_t i=0; i<num; i++){
        str.push_back(static_cast<char>(char_dist(rnd)));
    }
    return str;
}

std::vector<std::string> get_str_vector(size_t num){
    std::vector<std::string> vec;
    vec.reserve(num);
    for(size_t i=0; i<num; i++){
        vec.push_back(get_random_string(STRING_LEN));
    }
    return vec;
}

void partition_i(std::string& vec){
    std::partition(vec.begin(), vec.end(), [](char el){return el=='i';});
}


static void BM_ForEachVecInt(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::uniform_int_distribution<int> dist(0, 100000);
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    for (auto _ : state) {
        std::for_each(vec.begin(), vec.end(), [](int& el){el += 10;});
    }
}


static void BM_RangeBasedVecInt(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::uniform_int_distribution<int> dist(0, 100000);
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    for (auto _ : state) {
        for(auto& el : vec){
            el += 10;
        }
    }
}


static void BM_ForEachVecStr(benchmark::State& state) {
    std::vector<std::string> vec = get_str_vector(state.range(0));
    for (auto _ : state) {
        std::for_each(vec.begin(), vec.end(), [](std::string& el){
            partition_i(el);});
    }
}


static void BM_RangeBasedVecStr(benchmark::State& state) {
    std::vector<std::string> vec = get_str_vector(state.range(0));
    for (auto _ : state) {
        for(auto& el : vec){
            partition_i(el);
        }
    }
}





// Register the function as a benchmark
BENCHMARK(BM_ForEachVecInt)->Arg(ELEMENT_NUM);
BENCHMARK(BM_RangeBasedVecInt)->Arg(ELEMENT_NUM);
BENCHMARK(BM_ForEachVecStr)->Arg(ELEMENT_NUM);
BENCHMARK(BM_RangeBasedVecStr)->Arg(ELEMENT_NUM);

// Run the benchmark
BENCHMARK_MAIN();
