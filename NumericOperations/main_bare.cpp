#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <type_traits>

#include "benchmark/benchmark.h"

#define MIN_VAL 1
#define MAX_VAL 100

template <typename T>
T get_rnd_val() {
  std::random_device rnd;
  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist_real{MIN_VAL, MAX_VAL};
    return dist_real(rnd);
  } else {
    std::uniform_int_distribution<T> dist_int{MIN_VAL, MAX_VAL};
    return dist_int(rnd);
  }
}

//===========================COMPARE==========================================

static void BM_Int8Compare(benchmark::State& state) {
  for (auto _ : state) {
    auto lhs = get_rnd_val<int8_t>();
    auto rhs = get_rnd_val<int8_t>();
    benchmark::DoNotOptimize(lhs < rhs);
  }
}

static void BM_Int8Compare_BS(benchmark::State& state) {
  for (auto _ : state) {
    auto lhs = get_rnd_val<int8_t>();
    auto rhs = get_rnd_val<int8_t>();
    benchmark::DoNotOptimize(lhs);
    benchmark::DoNotOptimize(rhs);
  }
}

BENCHMARK(BM_Int8Compare);
BENCHMARK(BM_Int8Compare_BS);
// Run the benchmark
BENCHMARK_MAIN();
