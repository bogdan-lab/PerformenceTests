#include <deque>
#include <map>
#include <random>

#include "benchmark/benchmark.h"

struct Point {
  time_t timestamp = 0;
  double value = 0.0;
  std::map<int, double> details;
};

using DataRow = std::deque<Point>;

DataRow GenerateRow(int row_len, int detail_len) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> r_dist(0, 1);
  std::uniform_int_distribution<int> i_dist(0, 100000);
  DataRow result;
  while (row_len--) {
    result.emplace_back();
    result.back().timestamp = i_dist(rnd);
    for (int i = 0; i < detail_len; ++i) {
      double val = r_dist(rnd);
      result.back().details.emplace(i, val);
      result.back().value += val;
    }
  }
  return result;
}

void DestroyRow(DataRow& data) {
  DataRow tmp;
  std::swap(tmp, data);
}

static void DestructionBM(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    DataRow row =
        GenerateRow(/*row_len=*/state.range(0), /*detail_len=*/state.range(1));
    state.ResumeTiming();
    benchmark::DoNotOptimize(row);
    DestroyRow(row);
    benchmark::DoNotOptimize(row);
  }
}

// Register the function as a benchmark
BENCHMARK(DestructionBM)
    ->ArgsProduct({{10, 100, 1000, 10000}, {10, 100, 1000, 10000}});

// Run the benchmark
BENCHMARK_MAIN();
