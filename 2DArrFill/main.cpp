#include "benchmark/benchmark.h"
#include <random>
#include <vector>
#include <utility>

std::mt19937 rnd(42);


std::vector<std::pair<double, double>> modular_fill(size_t x_num, size_t y_num) {
    std::vector<std::pair<double, double>> vec;
    size_t num = x_num*y_num;
    vec.reserve(num);
    for(size_t i=0; i<num; i++) {
        vec.push_back({i%x_num, i/x_num});
    }
    return vec;
}



std::vector<std::pair<double, double>> double_for_fill(size_t x_num, size_t y_num) {
    std::vector<std::pair<double, double>> vec;
    size_t num = x_num*y_num;
    vec.reserve(num);
    for(size_t i=0; i<x_num; i++) {
        for(size_t j=0; j<y_num; j++) {
            vec.push_back({i, j});
        }
    }
    return vec;
}




static void BM_Modular(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<std::pair<double, double>> vec = modular_fill(state.range(0), state.range(1));
        benchmark::DoNotOptimize(vec);
    }
}


static void BM_DoubleFor(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<std::pair<double, double>> vec = double_for_fill(state.range(0), state.range(1));
        benchmark::DoNotOptimize(vec);
    }
}




// Register the function as a benchmark
BENCHMARK(BM_Modular)->ArgsProduct({{1<<9, 1<<10, 1<<11}, {1<<9, 1<<10, 1<<11}});
BENCHMARK(BM_DoubleFor)->ArgsProduct({{1<<9, 1<<10, 1<<11}, {1<<9, 1<<10, 1<<11}});

// Run the benchmark
BENCHMARK_MAIN();
