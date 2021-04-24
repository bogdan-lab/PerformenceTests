#include <vector>
#include <benchmark/benchmark.h>
#include <random>
#include <numeric>

#define VEC_SZIE 2<<10

std::mt19937 rnd(42);
std::uniform_real_distribution<double> dist;


double sum_together(const std::vector<std::vector<double>>& v) {
    double sum = 0;
    for(size_t i=0; i<v.size(); i++) {
        for(size_t j=0; j<v[0].size(); j++) {
            sum += v[i][j];
        }
    }
    return sum;
}



double sum_separately(const std::vector<std::vector<double>>& v) {
    double sum = 0.0;
    for(size_t i=0; i<v.size(); i++) {
        sum = std::accumulate(v[i].begin(), v[i].end(), sum);
    }
    return sum;
}



std::vector<double> mk_vec(size_t size){
    std::vector<double> v(size);
    std::generate(v.begin(), v.end(), [](){return dist(rnd);});
    return v;
}


static void BM_SumTogether(benchmark::State& state) {
    std::vector<std::vector<double>> v;
    for(size_t i=0; i<state.range(0); i++) {
        v.push_back(mk_vec(VEC_SZIE));
    }
    for (auto _ : state) {
        auto sum = sum_together(v);
        benchmark::DoNotOptimize(sum);
    }
}


static void BM_SumSeparately(benchmark::State& state) {
    std::vector<std::vector<double>> v;
    for(size_t i=0; i<state.range(0); i++) {
        v.push_back(mk_vec(VEC_SZIE));
    }
    for (auto _ : state) {
        auto sum = sum_separately(v);
        benchmark::DoNotOptimize(sum);
    }
}


BENCHMARK(BM_SumTogether)->RangeMultiplier(2)->Range(1, 10);
BENCHMARK(BM_SumSeparately)->RangeMultiplier(2)->Range(1, 10);

BENCHMARK_MAIN();
