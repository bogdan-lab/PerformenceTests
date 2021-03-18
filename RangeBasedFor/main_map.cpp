#include "benchmark/benchmark.h"
#include <algorithm>
#include <random>
#include <string>
#include <map>

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

std::vector<int> get_int_vec(size_t num){
    std::vector<int> vec(num);
    int cnt = 0;
    std::generate(vec.begin(), vec.end(), [&](){return ++cnt;});
    return vec;
}

std::map<int, std::string> get_map(size_t num){
    std::vector<int> keys = get_int_vec(num);
    std::vector<std::string> vals = get_str_vector(num);
    std::map<int, std::string> res;
    for(size_t i=0; i<num; i++){
        res[keys[i]] = vals[i];
    }
    return res;
}


int count_i(std::string& vec){
    return std::count(vec.begin(), vec.end(), 'i');
}


static void BM_ForEachMap(benchmark::State& state) {
    std::map<int, std::string> tst = get_map(state.range(0));
    int counter = 0;
    for (auto _ : state) {
        std::for_each(tst.begin(), tst.end(), [&](auto& el){
            counter += count_i(el.second);});
       benchmark::DoNotOptimize(counter /= 10000);
    }
}


static void BM_RangeBasedMap(benchmark::State& state) {
    std::map<int, std::string> tst = get_map(state.range(0));
    int counter = 0;
    for (auto _ : state) {
        for(auto& el : tst){
            benchmark::DoNotOptimize(counter += count_i(el.second));
        }
        benchmark::DoNotOptimize(counter /= 10000);
    }
}




// Register the function as a benchmark
BENCHMARK(BM_ForEachMap)->Arg(ELEMENT_NUM);
BENCHMARK(BM_RangeBasedMap)->Arg(ELEMENT_NUM);

// Run the benchmark
BENCHMARK_MAIN();
