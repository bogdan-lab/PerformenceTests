#include <vector>
#include <benchmark/benchmark.h>
#include <random>
#include <numeric>

#define VEC_SZIE 2<<10

std::mt19937 rnd(42);
std::uniform_real_distribution<double> dist;


double sum_together(const std::vector<double> v1, const std::vector<double> v2) {
    double sum = 0;
    for(size_t i=0; i<v1.size(); i++) {
        sum += v1[i] + v2[i];
    }
    return sum;
}



double sum_separately(const std::vector<double> v1, const std::vector<double> v2) {
    double sum = std::accumulate(v1.begin(), v1.end(), 0.0);
    sum = std::accumulate(v2.begin(), v2.end(), sum);
    return sum;
}



std::vector<double> mk_vec(size_t size){
    std::vector<double> v{size};
    std::generate(v.begin(), v.end(), [](){return dist(rnd);});
    return v;
}


static void BM_SumTogether(benchmark::State& state) {
    std::vector<double> v1 = mk_vec(VEC_SZIE);
    std::vector<double> v2 = mk_vec(VEC_SZIE);
    for (auto _ : state) {
        auto sum = sum_together(v1, v2);
        benchmark::DoNotOptimize(sum);
    }
}


static void BM_SumSeparately(benchmark::State& state) {
    std::vector<double> v1 = mk_vec(VEC_SZIE);
    std::vector<double> v2 = mk_vec(VEC_SZIE);
    for (auto _ : state) {
        auto sum = sum_separately(v1, v2);
        benchmark::DoNotOptimize(sum);
    }
}


BENCHMARK(BM_SumTogether);
BENCHMARK(BM_SumSeparately);

BENCHMARK_MAIN();
