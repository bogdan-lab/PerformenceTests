#include <algorithm>
#include <ctime>
#include <deque>
#include <queue>
#include <random>
#include <set>
#include <utility>

#include "benchmark/benchmark.h"
#include "source_generator.h"

struct SetComparator {
  bool operator()(const std::queue<double>* lhs,
                  const std::queue<double>* rhs) const {
    return lhs->front() < rhs->front();
  }
};

std::vector<double> SolveUsingSet(std::vector<std::queue<double>>& data) {
  std::vector<double> result;
  result.reserve(data.size() * data[0].size());
  std::set<std::queue<double>*, SetComparator> buff;
  for (auto& el : data) {
    buff.insert(&el);
  }

  while (!buff.empty()) {
    auto* top = *buff.begin();
    buff.erase(buff.begin());
    result.push_back(top->front());
    top->pop();
    if (!top->empty()) {
      buff.insert(top);
    }
  }

  return result;
}

static void GenerateSourceBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::queue<double>> sources;
    benchmark::DoNotOptimize(sources =
                                 GenerateSources(/*src_num=*/state.range(0),
                                                 /*src_len=*/state.range(1)));
  }
}

static void SetSolutionBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::queue<double>> sources;
    benchmark::DoNotOptimize(sources =
                                 GenerateSources(/*src_num=*/state.range(0),
                                                 /*src_len=*/state.range(1)));
    std::vector<double> res;
    benchmark::DoNotOptimize(res = SolveUsingSet(sources));
  }
}

std::vector<double> SolveUsingHeap(std::vector<std::queue<double>>& data) {
  std::vector<double> result;
  result.reserve(data.size() * data[0].size());
  std::vector<std::queue<double>*> buff;
  buff.reserve(data.size());
  for (auto& el : data) {
    buff.push_back(&el);
  }
  std::make_heap(buff.begin(), buff.end());

  auto heap_comp = [](const std::queue<double>* lhs,
                      const std::queue<double>* rhs) {
    return lhs->front() > rhs->front();
  };

  while (!buff.empty()) {
    std::pop_heap(buff.begin(), buff.end(), heap_comp);
    auto* top = buff.back();
    buff.pop_back();
    result.push_back(top->front());
    top->pop();
    if (!top->empty()) {
      buff.push_back(top);
      std::push_heap(buff.begin(), buff.end(), heap_comp);
    }
  }

  return result;
}

static void HeapSolutionBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::queue<double>> sources;
    benchmark::DoNotOptimize(sources =
                                 GenerateSources(/*src_num=*/state.range(0),
                                                 /*src_len=*/state.range(1)));
    std::vector<double> res;
    benchmark::DoNotOptimize(res = SolveUsingHeap(sources));
  }
}

std::vector<double> SolveUsingSortedVector(
    std::vector<std::queue<double>>& data) {
  std::vector<double> result;
  result.reserve(data.size() * data[0].size());
  std::vector<std::queue<double>*> buff;
  buff.reserve(data.size());
  for (auto& el : data) {
    buff.push_back(&el);
  }
  auto comp = [](const std::queue<double>* lhs, const std::queue<double>* rhs) {
    return lhs->front() > rhs->front();
  };
  std::sort(buff.begin(), buff.end(), comp);

  while (!buff.empty()) {
    auto* top = buff.back();
    buff.pop_back();
    result.push_back(top->front());
    top->pop();
    if (!top->empty()) {
      auto it = std::lower_bound(buff.begin(), buff.end(), top, comp);
      buff.insert(it, top);
    }
  }

  return result;
}

static void SortVectorSolutionBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::queue<double>> sources;
    benchmark::DoNotOptimize(sources =
                                 GenerateSources(/*src_num=*/state.range(0),
                                                 /*src_len=*/state.range(1)));
    std::vector<double> res;
    benchmark::DoNotOptimize(res = SolveUsingSortedVector(sources));
  }
}

std::vector<double> SolveUsingMin(std::vector<std::queue<double>>& data) {
  std::vector<double> result;
  result.reserve(data.size() * data[0].size());
  std::vector<std::queue<double>*> buff;
  buff.reserve(data.size());
  for (auto& el : data) {
    buff.push_back(&el);
  }

  while (!buff.empty()) {
    auto it = std::min_element(buff.begin(), buff.end(),
                               [](const auto* lhs, const auto* rhs) {
                                 return lhs->front() < rhs->front();
                               });
    auto* top = *it;
    result.push_back(top->front());
    top->pop();
    if (top->empty()) {
      std::swap(*it, buff.back());
      buff.pop_back();
    }
  }

  return result;
}

static void MinSolutionBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::queue<double>> sources;
    benchmark::DoNotOptimize(sources =
                                 GenerateSources(/*src_num=*/state.range(0),
                                                 /*src_len=*/state.range(1)));
    std::vector<double> res;
    benchmark::DoNotOptimize(res = SolveUsingMin(sources));
  }
}

#define CASE_VALUES 10, 100, 500

// Register the function as a benchmark
BENCHMARK(GenerateSourceBM)->ArgsProduct({{CASE_VALUES}, {CASE_VALUES}});
BENCHMARK(SetSolutionBM)->ArgsProduct({{CASE_VALUES}, {CASE_VALUES}});
BENCHMARK(HeapSolutionBM)->ArgsProduct({{CASE_VALUES}, {CASE_VALUES}});
BENCHMARK(SortVectorSolutionBM)->ArgsProduct({{CASE_VALUES}, {CASE_VALUES}});
// Very slow!
// BENCHMARK(MinSolutionBM)->ArgsProduct({{CASE_VALUES}, {CASE_VALUES}});

// Run the benchmark
BENCHMARK_MAIN();
