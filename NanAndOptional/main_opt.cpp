#include "benchmark/benchmark.h"

#include<optional>
#include<cmath>
#include <random>


std::mt19937 rnd(42);
std::uniform_real_distribution<double> dist(16.0, 23.0);


static void BM_OptSaveAndOp(benchmark::State& state){
    std::optional<double> val = dist(rnd);
    std::optional<double> res = M_PI;
    for(auto _ : state){
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 * *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 / *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 + *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 - *val));
    }
}

static void BM_OptOpOnly(benchmark::State& state){
    std::optional<double> val = dist(rnd);
    double res = M_PI;
    for(auto _ : state){
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 * *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 / *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 + *val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 - *val));
    }
}

static void BM_DoubleOperations(benchmark::State& state){
    double val = dist(rnd);
    double res = M_PI;
    for(auto _ : state){
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 * val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 / val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 + val));
        benchmark::DoNotOptimize(res = std::sqrt(1234.567 - val));
    }
}



// Register the function as a benchmark
BENCHMARK(BM_OptOpOnly);
BENCHMARK(BM_OptSaveAndOp);
BENCHMARK(BM_DoubleOperations);

// Run the benchmark
BENCHMARK_MAIN();
