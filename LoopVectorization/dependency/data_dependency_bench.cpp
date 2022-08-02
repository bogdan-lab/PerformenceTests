
#include <vector>
#include<benchmark/benchmark.h>
#include <random>
#include <iostream>

int f_no_dep(std::vector<int> x);
int f_close_fwd(std::vector<int> x);
int f_close_bwd(std::vector<int> x);
int f_far_fwd(std::vector<int> x, size_t step);
int f_far_bwd(std::vector<int> x, size_t step);
int f_close_bwd_SEP(std::vector<int> x);

template<size_t Step>
int f_far_fwd(std::vector<int> x){
    int sum = 0;
    for(size_t i=0; i<x.size()-Step; i++){
        x[i] = (x[i] + x[i+Step])/2;
        sum+=x[i];
    }
    return sum;
}

template<size_t Step>
int f_far_bwd(std::vector<int> x){
    int sum = 0;
    for(size_t i=Step; i<x.size(); i++){
        x[i] = (x[i-Step]+x[i])/2;
        sum+=x[i];
    }
    return sum;
}


std::mt19937 rnd(42);
std::uniform_int_distribution<int> dist(0, 1000);

static void BM_Accumulate(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = std::accumulate(vec.begin(), vec.end(), 0));
    }
}



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


static void BM_CloseBwd_SEP(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_close_bwd_SEP(vec));
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

static void BM_FarFwd_TMPL_1(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_fwd<1>(vec));
    }
}

static void BM_FarFwd_TMPL_3(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_fwd<3>(vec));
    }
}

static void BM_FarFwd_TMPL_4(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_fwd<4>(vec));
    }
}

static void BM_FarBwd_TMPL_1(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_bwd<1>(vec));
    }
}

static void BM_FarBwd_TMPL_3(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_bwd<3>(vec));
    }
}

static void BM_FarBwd_TMPL_4(benchmark::State& state) {
    std::vector<int> vec(state.range(0));
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    int sum = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(sum = f_far_bwd<4>(vec));
    }
}


BENCHMARK(BM_NoDepend)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_Accumulate)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_CloseFwd)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_CloseBwd)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_CloseBwd_SEP)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_FarFwd)->ArgsProduct({{100000}, {1,3,4}});
BENCHMARK(BM_FarBwd)->ArgsProduct({{100000}, {1,3,4}});
BENCHMARK(BM_FarFwd_TMPL_1)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_FarBwd_TMPL_1)->ArgsProduct({{100000}, {1}});
BENCHMARK(BM_FarFwd_TMPL_3)->ArgsProduct({{100000}, {3}});
BENCHMARK(BM_FarBwd_TMPL_3)->ArgsProduct({{100000}, {3}});
BENCHMARK(BM_FarFwd_TMPL_4)->ArgsProduct({{100000}, {4}});
BENCHMARK(BM_FarBwd_TMPL_4)->ArgsProduct({{100000}, {4}});

// Run the benchmark
BENCHMARK_MAIN();
