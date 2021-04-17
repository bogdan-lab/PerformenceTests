#include<benchmark/benchmark.h>
#include<vector>
#include<random>

std::mt19937 rnd(42);

std::vector<double> get_1D(size_t num){
    std::uniform_real_distribution<double> dist{0.0, 1.0};
    std::vector<double> vec(num);
    std::generate(vec.begin(), vec.end(), [&](){return dist(rnd);});
    return vec;
}


std::vector<std::vector<double>> get_2D(size_t x_size, size_t y_size){
    std::vector<std::vector<double>> vec;
    for(size_t i=0; i<y_size; i++) {
        vec.push_back(get_1D(x_size));
    }
    return vec;
}


double sum_1D(const std::vector<double>& vec) {
    return std::accumulate(vec.begin(), vec.end(), 0);
}

double sum_2D(const std::vector<std::vector<double>>& vec) {
    double sum = 0;
    for(const auto& el : vec) {
        sum += sum_1D(el);
    }
    return sum;
}

static void BM_Sum1D(benchmark::State& state) {
    auto vec = get_1D(state.range(0)*state.range(1));
    for (auto _ : state) {
        auto sum = sum_1D(vec);
        benchmark::DoNotOptimize(sum);
    }
}


static void BM_Sum2D(benchmark::State& state) {
    auto vec = get_2D(state.range(0), state.range(1));
    for (auto _ : state) {
        auto sum = sum_2D(vec);
        benchmark::DoNotOptimize(sum);
    }
}


BENCHMARK(BM_Sum1D)->ArgsProduct({{1<<9, 1<<10, 1<<11}, {1<<9, 1<<10, 1<<11}});
BENCHMARK(BM_Sum2D)->ArgsProduct({{1<<9, 1<<10, 1<<11}, {1<<9, 1<<10, 1<<11}});

// Run the benchmark
BENCHMARK_MAIN();


