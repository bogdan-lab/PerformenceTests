#include <algorithm>
#include <random>
#include <vector>
#include <time.h>

#include<benchmark/benchmark.h>

static std::mt19937 rnd(0);

std::vector<int> generate_data(const size_t size){
    //std::mt19937 rnd(static_cast<uint>(time(NULL)));
    std::uniform_int_distribution<int> dist(0);
    std::vector<int> data;
    data.reserve(size);
    for(size_t i=0; i<size; i++){
        data.push_back(dist(rnd));
    }
    return data;
}


static void Baseline(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    size_t sum = 0;
    for(auto _ : state) {
        benchmark::DoNotOptimize(
            sum = std::accumulate(data.begin(), data.begin()+data.size()/2, 0)
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }

}


static void WithPartition(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    size_t sum = 0;
    for(auto _ : state) {
        auto it = std::partition(data.begin(), data.end(), [](const int el){return el%2==0;});
        benchmark::DoNotOptimize(
            sum = std::accumulate(data.begin(), it, 0)
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }
}


static void NoPartition(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    std::uniform_int_distribution<int> dist(0, 1000);
    size_t sum = 0;
    for(auto _ : state) {
        for(size_t i=0; i<data.size(); i++){
            benchmark::DoNotOptimize(sum += data[i]%2 ? data[i] : 0);
        }
        std::shuffle(data.begin(), data.end(), rnd);
        sum = dist(rnd);
    }
}


// Register the function as a benchmark
BENCHMARK(Baseline)->Arg(100)->Arg(10'000)->Arg(1'000'000)->Arg(10'000'000);
BENCHMARK(WithPartition)->Arg(100)->Arg(10'000)->Arg(1'000'000)->Arg(10'000'000);
BENCHMARK(NoPartition)->Arg(100)->Arg(10'000)->Arg(1'000'000)->Arg(10'000'000);
// Run the benchmark
BENCHMARK_MAIN();
