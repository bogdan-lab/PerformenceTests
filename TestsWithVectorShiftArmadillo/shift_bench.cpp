#include <benchmark/benchmark.h>

#include <armadillo>
#include <limits>
#include <random>
#include <vector>

arma::vec GenerateVector(size_t size) {
  std::mt19937 rnd(size);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
  arma::vec result(size);
  for (auto& el : result) {
    el = dist(rnd);
  }
  return result;
}

arma::vec RotateAndConvert(std::vector<double>& vec, size_t num) {
  std::rotate(vec.begin(), vec.begin() + num, vec.end());
  return arma::conv_to<arma::vec>::from(vec);
}

static void BM_StdVecRotateWithConversion(benchmark::State& state) {
  auto test =
      arma::conv_to<std::vector<double>>::from(GenerateVector(state.range(0)));
  for (auto _ : state) {
    arma::vec vec_copy = RotateAndConvert(test, 1);
    benchmark::DoNotOptimize(vec_copy);
  }
}

static void BM_StdVecRotateNoConversion(benchmark::State& state) {
  auto test =
      arma::conv_to<std::vector<double>>::from(GenerateVector(state.range(0)));
  for (auto _ : state) {
    std::rotate(test.begin(), test.begin() + 1, test.end());
    benchmark::DoNotOptimize(test);
  }
}

static void BM_ArmadilloShift(benchmark::State& state) {
  arma::vec test = GenerateVector(state.range(0));
  for (auto _ : state) {
    test = arma::shift(test, -1);
    benchmark::DoNotOptimize(test);
  }
}

static void BM_StdRotateArmaVecInplace(benchmark::State& state) {
  arma::vec test = GenerateVector(state.range(0));
  for (auto _ : state) {
    std::rotate(test.begin(), test.begin() + 1, test.end());
    benchmark::DoNotOptimize(test);
  }
}

BENCHMARK(BM_ArmadilloShift)->DenseRange(10, 300, 50);
BENCHMARK(BM_StdRotateArmaVecInplace)->DenseRange(10, 300, 50);
BENCHMARK(BM_StdVecRotateNoConversion)->DenseRange(10, 300, 50);
BENCHMARK(BM_StdVecRotateWithConversion)->DenseRange(10, 300, 50);

BENCHMARK_MAIN();
