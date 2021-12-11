#include <benchmark/benchmark.h>

#include <algorithm>
#include <armadillo>
#include <limits>
#include <random>

static void BM_RotateArmadilloLeft(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::lowest(),
      std::numeric_limits<double>::max()};
  arma::vec test(state.range(0));
  std::generate(test.begin(), test.end(), [&]() { return dist(rnd); });
  for (auto _ : state) {
    std::rotate(test.begin(), test.begin() + state.range(1), test.end());
    benchmark::DoNotOptimize(test);
  }
}

static void BM_RotateArmadilloRight(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::lowest(),
      std::numeric_limits<double>::max()};
  arma::vec test(state.range(0));

  std::generate(test.begin(), test.end(), [&]() { return dist(rnd); });

  for (auto _ : state) {
    std::rotate(test.begin(), test.end() - state.range(1), test.end());
    benchmark::DoNotOptimize(test);
  }
}

BENCHMARK(BM_RotateArmadilloLeft)
    ->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10, 20}});
BENCHMARK(BM_RotateArmadilloRight)
    ->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10, 20}});
