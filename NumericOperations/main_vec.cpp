#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <type_traits>

#include "benchmark/benchmark.h"

#define SIZE 1 << 15
#define MIN_VAL 1
#define MAX_VAL 100

template <typename T>
std::vector<T> create_vector(size_t s) {
  std::random_device rnd;
  std::function<T()> generator;
  if constexpr (std::is_floating_point_v<T>) {
    std::uniform_real_distribution<T> dist{MIN_VAL, MAX_VAL};
    generator = [&rnd, dist]() mutable { return dist(rnd); };
  } else {
    std::uniform_int_distribution<T> dist{MIN_VAL, MAX_VAL};
    generator = [&rnd, dist]() mutable { return dist(rnd); };
  }
  std::vector<T> vec(s);
  std::generate(vec.begin(), vec.end(), generator);
  return vec;
}

//===========================COMPARE==========================================

static void BM_Int8Compare(benchmark::State& state) {
  auto lhs = create_vector<int8_t>(SIZE);
  auto rhs = create_vector<int8_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      bool res = lhs[i] < rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int32Compare(benchmark::State& state) {
  auto lhs = create_vector<int32_t>(SIZE);
  auto rhs = create_vector<int32_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      bool res = lhs[i] < rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int64Compare(benchmark::State& state) {
  auto lhs = create_vector<int64_t>(SIZE);
  auto rhs = create_vector<int64_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      bool res = lhs[i] < rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_FloatCompare(benchmark::State& state) {
  auto lhs = create_vector<float>(SIZE);
  auto rhs = create_vector<float>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      bool res = lhs[i] < rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_DoubleCompare(benchmark::State& state) {
  auto lhs = create_vector<double>(SIZE);
  auto rhs = create_vector<double>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      bool res = lhs[i] < rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

//===============================MULTIPLY=====================================

static void BM_Int8Multiply(benchmark::State& state) {
  auto lhs = create_vector<int8_t>(SIZE);
  auto rhs = create_vector<int8_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] * rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int32Multiply(benchmark::State& state) {
  auto lhs = create_vector<int32_t>(SIZE);
  auto rhs = create_vector<int32_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] * rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int64Multiply(benchmark::State& state) {
  auto lhs = create_vector<int64_t>(SIZE);
  auto rhs = create_vector<int64_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] * rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_FloatMultiply(benchmark::State& state) {
  auto lhs = create_vector<float>(SIZE);
  auto rhs = create_vector<float>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] * rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_DoubleMultiply(benchmark::State& state) {
  auto lhs = create_vector<double>(SIZE);
  auto rhs = create_vector<double>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] * rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

//==============================DIVIDE==========================================

static void BM_Int8Divide(benchmark::State& state) {
  auto lhs = create_vector<int8_t>(SIZE);
  auto rhs = create_vector<int8_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] / rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int32Divide(benchmark::State& state) {
  auto lhs = create_vector<int32_t>(SIZE);
  auto rhs = create_vector<int32_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] / rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int64Divide(benchmark::State& state) {
  auto lhs = create_vector<int64_t>(SIZE);
  auto rhs = create_vector<int64_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] / rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_FloatDivide(benchmark::State& state) {
  auto lhs = create_vector<float>(SIZE);
  auto rhs = create_vector<float>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] / rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_DoubleDivide(benchmark::State& state) {
  auto lhs = create_vector<double>(SIZE);
  auto rhs = create_vector<double>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] / rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

//==============================PLUS===========================================

static void BM_Int8Plus(benchmark::State& state) {
  auto lhs = create_vector<int8_t>(SIZE);
  auto rhs = create_vector<int8_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] + rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int32Plus(benchmark::State& state) {
  auto lhs = create_vector<int32_t>(SIZE);
  auto rhs = create_vector<int32_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] + rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int64Plus(benchmark::State& state) {
  auto lhs = create_vector<int64_t>(SIZE);
  auto rhs = create_vector<int64_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] + rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_FloatPlus(benchmark::State& state) {
  auto lhs = create_vector<float>(SIZE);
  auto rhs = create_vector<float>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] + rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_DoublePlus(benchmark::State& state) {
  auto lhs = create_vector<double>(SIZE);
  auto rhs = create_vector<double>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] + rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

//===================MINUS===============================

static void BM_Int8Minus(benchmark::State& state) {
  auto lhs = create_vector<int8_t>(SIZE);
  auto rhs = create_vector<int8_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] - rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int32Minus(benchmark::State& state) {
  auto lhs = create_vector<int32_t>(SIZE);
  auto rhs = create_vector<int32_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] - rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_Int64Minus(benchmark::State& state) {
  auto lhs = create_vector<int64_t>(SIZE);
  auto rhs = create_vector<int64_t>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] - rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_FloatMinus(benchmark::State& state) {
  auto lhs = create_vector<float>(SIZE);
  auto rhs = create_vector<float>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] - rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

static void BM_DoubleMinus(benchmark::State& state) {
  auto lhs = create_vector<double>(SIZE);
  auto rhs = create_vector<double>(SIZE);
  for (auto _ : state) {
    for (size_t i = 0; i < lhs.size(); ++i) {
      auto res = lhs[i] - rhs[i];
      benchmark::DoNotOptimize(res);
    }
  }
}

BENCHMARK(BM_Int8Compare);
BENCHMARK(BM_Int32Compare);
BENCHMARK(BM_Int64Compare);
BENCHMARK(BM_FloatCompare);
BENCHMARK(BM_DoubleCompare);

BENCHMARK(BM_Int8Multiply);
BENCHMARK(BM_Int32Multiply);
BENCHMARK(BM_Int64Multiply);
BENCHMARK(BM_FloatMultiply);
BENCHMARK(BM_DoubleMultiply);

BENCHMARK(BM_Int8Divide);
BENCHMARK(BM_Int32Divide);
BENCHMARK(BM_Int64Divide);
BENCHMARK(BM_FloatDivide);
BENCHMARK(BM_DoubleDivide);

BENCHMARK(BM_Int8Plus);
BENCHMARK(BM_Int32Plus);
BENCHMARK(BM_Int64Plus);
BENCHMARK(BM_FloatPlus);
BENCHMARK(BM_DoublePlus);

BENCHMARK(BM_Int8Minus);
BENCHMARK(BM_Int32Minus);
BENCHMARK(BM_Int64Minus);
BENCHMARK(BM_FloatMinus);
BENCHMARK(BM_DoubleMinus);

// Run the benchmark
BENCHMARK_MAIN();
