
#include <vector>
#include<benchmark/benchmark.h>
#include <random>
#include <iostream>

int f_no_dep(std::vector<int> x);
int f_close_fwd(std::vector<int> x);
int f_close_bwd(std::vector<int> x);
int f_far_fwd(std::vector<int> x, size_t step);
int f_far_bwd(std::vector<int> x, size_t step);



std::mt19937 rnd(42);
std::uniform_int_distribution<int> dist(0, 1000);

static void BM_NoDepend(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_no_dep(vec));
    }
}

static void BM_CloseFwd(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_close_fwd(vec));
    }
}

static void BM_CloseBwd(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_close_bwd(vec));
    }
}

static void BM_FarFwd(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_fwd(vec, state.range(1)));
    }
}

static void BM_FarBwd(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_bwd(vec, state.range(1)));
    }
}




BENCHMARK(BM_NoDepend)->ArgsProduct({{1000, 10000, 100000}, {1}});
BENCHMARK(BM_CloseFwd)->ArgsProduct({{1000, 10000, 100000}, {1}});
BENCHMARK(BM_CloseBwd)->ArgsProduct({{1000, 10000, 100000}, {1}});
BENCHMARK(BM_FarFwd)->ArgsProduct({{1000, 10000, 100000}, {1,3,4}});
BENCHMARK(BM_FarBwd)->ArgsProduct({{1000, 10000, 100000}, {1,3,4}});

// Run the benchmark
BENCHMARK_MAIN();
