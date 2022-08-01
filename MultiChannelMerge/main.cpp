#include <algorithm>
#include <ctime>
#include <deque>
#include <queue>
#include <random>
#include <set>
#include <utility>

#include "benchmark/benchmark.h"

std::vector<std::queue<double>> GenerateSources(int src_num, int src_len) {
  std::mt19937 rnd(std::time(nullptr));
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::vector<std::queue<double>> result;
  result.reserve(src_num);
  while (src_num--) {
    std::vector<double> buff(src_len);
    std::generate(buff.begin(), buff.end(), [&]() { return dist(rnd); });
    std::sort(buff.begin(), buff.end());
    result.emplace_back();
    for (const auto& el : buff) {
      result.back().push(el);
    }
  }
  return result;
}

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
    auto sources =
        GenerateSources(/*src_num=*/state.range(0), /*src_len=*/state.range(1));
    benchmark::DoNotOptimize(sources);
  }
}

static void SetSolutionBM(benchmark::State& state) {
  for (auto _ : state) {
    auto sources =
        GenerateSources(/*src_num=*/state.range(0), /*src_len=*/state.range(1));
    benchmark::DoNotOptimize(sources);
    std::vector<double> res = SolveUsingSet(sources);
    benchmark::DoNotOptimize(res);
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
    auto sources =
        GenerateSources(/*src_num=*/state.range(0), /*src_len=*/state.range(1));
    benchmark::DoNotOptimize(sources);
    std::vector<double> res = SolveUsingHeap(sources);
    benchmark::DoNotOptimize(res);
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
    auto sources =
        GenerateSources(/*src_num=*/state.range(0), /*src_len=*/state.range(1));
    benchmark::DoNotOptimize(sources);
    std::vector<double> res = SolveUsingSortedVector(sources);
    benchmark::DoNotOptimize(res);
  }
}

// Register the function as a benchmark
BENCHMARK(GenerateSourceBM)
    ->ArgsProduct({{1, 10, 100, 1000}, {1, 10, 100, 1000}});
BENCHMARK(SetSolutionBM)->ArgsProduct({{1, 10, 100, 1000}, {1, 10, 100, 1000}});
BENCHMARK(HeapSolutionBM)
    ->ArgsProduct({{1, 10, 100, 1000}, {1, 10, 100, 1000}});
BENCHMARK(SortVectorSolutionBM)
    ->ArgsProduct({{1, 10, 100, 1000}, {1, 10, 100, 1000}});

// Run the benchmark
BENCHMARK_MAIN();
