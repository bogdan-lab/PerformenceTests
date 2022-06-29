#include <benchmark/benchmark.h>

#include <algorithm>
#include <functional>
#include <random>
#include <vector>

#include "outside_less.h"

std::vector<uint64_t> GenerateData(size_t size) {
  std::mt19937 rnd(0);
  std::vector<uint64_t> result(size);
  std::generate(result.begin(), result.end(), rnd);
  return result;
}

void BaselineCall(uint64_t& lhs, uint64_t& rhs) {
  if (rhs < lhs) {
    // benchmark::DoNotOptimize(lhs);
    // benchmark::DoNotOptimize(rhs);
    std::swap(lhs, rhs);
  }
}

static void Baseline(benchmark::State& state) {
  std::vector<uint64_t> data = GenerateData(1000);
  for (auto _ : state) {
    for (size_t i = 1; i < data.size(); ++i) {
      BaselineCall(data[i - 1], data[i]);
    }
  }
}

void FunctionPtrCall(uint64_t& lhs, uint64_t& rhs,
                     bool (*check_func)(const uint64_t&, const uint64_t&)) {
  if (check_func(rhs, lhs)) {
    // benchmark::DoNotOptimize(lhs);
    // benchmark::DoNotOptimize(rhs);
    std::swap(lhs, rhs);
  }
}

bool Less(const uint64_t& lhs, const uint64_t& rhs) { return lhs < rhs; }

static void FunctionPtr(benchmark::State& state) {
  std::vector<uint64_t> data = GenerateData(1000);
  for (auto _ : state) {
    for (size_t i = 1; i < data.size(); ++i) {
      FunctionPtrCall(data[i - 1], data[i], Less);
    }
  }
}

static void OutsideFunctionPtr(benchmark::State& state) {
  std::vector<uint64_t> data = GenerateData(1000);
  for (auto _ : state) {
    for (size_t i = 1; i < data.size(); ++i) {
      FunctionPtrCall(data[i - 1], data[i], OutsideLess);
    }
  }
}

void StdFunctionCall(
    uint64_t& lhs, uint64_t& rhs,
    std::function<bool(const uint64_t&, const uint64_t&)> check_func) {
  if (check_func(rhs, lhs)) {
    // benchmark::DoNotOptimize(lhs);
    // benchmark::DoNotOptimize(rhs);
    std::swap(lhs, rhs);
  }
}

static void StdFunction(benchmark::State& state) {
  std::vector<uint64_t> data = GenerateData(1000);
  for (auto _ : state) {
    for (size_t i = 1; i < data.size(); ++i) {
      StdFunctionCall(data[i - 1], data[i], std::less<uint64_t>());
    }
  }
}

template <typename Callback>
void TemplateCall(uint64_t& lhs, uint64_t& rhs, Callback check_func) {
  if (check_func(rhs, lhs)) {
    // benchmark::DoNotOptimize(lhs);
    // benchmark::DoNotOptimize(rhs);
    std::swap(lhs, rhs);
  }
}

static void Template(benchmark::State& state) {
  std::vector<uint64_t> data = GenerateData(1000);
  for (auto _ : state) {
    for (size_t i = 1; i < data.size(); ++i) {
      TemplateCall(data[i - 1], data[i], std::less<uint64_t>());
    }
  }
}

BENCHMARK(Baseline);
BENCHMARK(StdFunction);
BENCHMARK(FunctionPtr);
BENCHMARK(OutsideFunctionPtr);
BENCHMARK(Template);