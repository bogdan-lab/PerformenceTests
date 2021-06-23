#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "benchmark/benchmark.h"

#define ELEMENT_NUM 10000

std::vector<double> generate_double(size_t n) {
  std::vector<double> vec;
  vec.reserve(n);
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dbl_dist{-6.0e9, 6.0e9};
  std::generate_n(std::back_inserter(vec), n, [&]() { return dbl_dist(rnd); });
  return vec;
}

std::vector<int> generate_int(size_t n) {
  std::vector<int> vec;
  vec.reserve(n);
  std::mt19937 rnd(42);
  std::uniform_int_distribution<int> int_dist{-1000, 1000};
  std::generate_n(std::back_inserter(vec), n, [&]() { return int_dist(rnd); });
  return vec;
}

std::vector<std::string> generate_string(size_t n, size_t length = 50) {
  std::vector<std::string> vec(n);
  std::mt19937 rnd(42);
  std::uniform_int_distribution<uint8_t> char_dist{65, 125};
  for (auto& el : vec) {
    el.reserve(length);
    for (size_t i = 0; i < length; ++i) {
      el.push_back(static_cast<char>(char_dist(rnd)));
    }
  }
  return vec;
}

static void BM_StringStream(benchmark::State& state) {
  std::vector<int> vec_int = generate_int(ELEMENT_NUM);
  std::vector<double> vec_dbl = generate_double(ELEMENT_NUM);
  std::vector<std::string> vec_string = generate_string(ELEMENT_NUM);
  for (auto _ : state) {
    for (size_t i = 0; i < ELEMENT_NUM; ++i) {
      std::stringstream ss;
      ss << vec_string[i] << " " << vec_dbl[i] << " " << vec_int[i] << "\n";
      std::string res = ss.str();
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Append(benchmark::State& state) {
  std::vector<int> vec_int = generate_int(ELEMENT_NUM);
  std::vector<double> vec_dbl = generate_double(ELEMENT_NUM);
  std::vector<std::string> vec_string = generate_string(ELEMENT_NUM);
  for (auto _ : state) {
    for (size_t i = 0; i < ELEMENT_NUM; ++i) {
      std::string res;
      res.append(vec_string[i])
          .append(" ")
          .append(std::to_string(vec_dbl[i]))
          .append(" ")
          .append(std::to_string(vec_int[i]))
          .append("\n");
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Plus(benchmark::State& state) {
  std::vector<int> vec_int = generate_int(ELEMENT_NUM);
  std::vector<double> vec_dbl = generate_double(ELEMENT_NUM);
  std::vector<std::string> vec_string = generate_string(ELEMENT_NUM);
  for (auto _ : state) {
    for (size_t i = 0; i < ELEMENT_NUM; ++i) {
      std::string res = vec_string[i] + " " + std::to_string(vec_dbl[i]) + " " +
                        std::to_string(vec_int[i]) + "\n";
      benchmark::DoNotOptimize(res);
    }
  }
}

// sprintf
// fmt

// Register the function as a benchmark
BENCHMARK(BM_StringStream);
BENCHMARK(BM_Append);
BENCHMARK(BM_Plus);

// Run the benchmark
BENCHMARK_MAIN();
