#include <benchmark/benchmark.h>

#include <armadillo>
#include <limits>
#include <random>
#include <vector>

// class SimpleCycleVector {
// public:
//  SimpleCycleVector(const arma::vec& input) : data_(input) {}
//
//  void Shift();
//
//  const arma::vec& GetData() const { return data_; }
//
// private:
//  arma::vec data_;
//};

arma::vec GenerateVector(size_t size) {
  std::mt19937 rnd;
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::min(), std::numeric_limits<double>::max()};
  arma::vec result(size);
  for (auto& el : result) {
    el = dist(rnd);
  }
  return result;
}

arma::vec RotateAndConvert(std::vector<double>& vec, size_t num) {
  std::rotate(vec.begin(), vec.begin() + vec.size() - num, vec.end());
  return arma::conv_to<arma::vec>::from(vec);
}

static void BMStdVecRotateWithConversion(benchmark::State& state) {
  auto test =
      arma::conv_to<std::vector<double>>::from(GenerateVector(state.range(0)));
  for (auto _ : state) {
    arma::vec vec_copy = RotateAndConvert(test, 1);
    benchmark::DoNotOptimize(vec_copy);
  }
}

static void BMStdVecRotateNoConversion(benchmark::State& state) {
  auto test =
      arma::conv_to<std::vector<double>>::from(GenerateVector(state.range(0)));
  for (auto _ : state) {
    std::rotate(test.begin(), test.begin() + test.size() - 1, test.end());
    benchmark::DoNotOptimize(test);
  }
}

static void BMArmadilloShift(benchmark::State& state) {
  arma::vec test = GenerateVector(state.range(0));
  for (auto _ : state) {
    test = arma::shift(test, 1);
    benchmark::DoNotOptimize(test);
  }
}

static void BMStdRotateArmaVecInplace(benchmark::State& state) {
  arma::vec test = GenerateVector(state.range(0));
  for (auto _ : state) {
    std::rotate(test.begin(), test.begin() + test.size() - 1, test.end());
    benchmark::DoNotOptimize(test);
  }
}

BENCHMARK(BMArmadilloShift)->DenseRange(10, 300, 50);
BENCHMARK(BMStdRotateArmaVecInplace)->DenseRange(10, 300, 50);
BENCHMARK(BMStdVecRotateNoConversion)->DenseRange(10, 300, 50);
BENCHMARK(BMStdVecRotateWithConversion)->DenseRange(10, 300, 50);

// Run the benchmark
BENCHMARK_MAIN();
