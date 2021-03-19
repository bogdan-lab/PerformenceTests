#include "benchmark/benchmark.h"
#include <random>
#include <numeric>
#include <optional>
#include <vector>
#include <cmath>

#define TEST_COUNT 10000

std::mt19937 rnd(42);


std::vector<double> generate_data_with_Nan(size_t num){
    std::vector<int> vec(num, 0);
    std::iota(vec.begin(), vec.end(), 0);
    std::vector<double> ret;
    ret.reserve(vec.size());
    for(const auto el : vec){
        ret.push_back(el%2 ? 1 : std::numeric_limits<double>::quiet_NaN());
    }
    return ret;
}

std::vector<std::optional<double>> generate_data_with_Opt(size_t num){
    std::vector<int> vec(num, 0);
    std::iota(vec.begin(), vec.end(), 0);
    std::vector<std::optional<double>> ret;
    ret.reserve(vec.size());
    for(const auto el : vec){
        if(el%2) ret.push_back(1.0);
        else ret.push_back(std::nullopt);
    }
    return ret;
}

static void BM_Nan(benchmark::State& state) {
    std::vector<double> vec = generate_data_with_Nan(state.range(0));
    size_t sum = 0;
    for (auto _ : state) {
        for(const auto el : vec){
            benchmark::DoNotOptimize( sum += std::isnan(el) ? 1 : 0);
        }
       benchmark::DoNotOptimize(sum /= state.range(0));
    }
}


static void BM_Opt(benchmark::State& state) {
    std::vector<std::optional<double>> vec = generate_data_with_Opt(state.range(0));
    size_t sum = 0;
    for (auto _ : state) {
        for(const auto el : vec){
            benchmark::DoNotOptimize( sum += el ? 1 : 0);
        }
       benchmark::DoNotOptimize(sum /= state.range(0));
    }
}




// Register the function as a benchmark
BENCHMARK(BM_Nan)->Arg(TEST_COUNT);
BENCHMARK(BM_Opt)->Arg(TEST_COUNT);

// Run the benchmark
BENCHMARK_MAIN();
