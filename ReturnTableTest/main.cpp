#include <benchmark/benchmark.h>

#include <algorithm>
#include <cmath>
#include <ctime>
#include <map>
#include <random>
#include <unordered_map>
#include <vector>

class MapReturnDataPoint {
 public:
  explicit MapReturnDataPoint(time_t t) : timestamp_(t) {}

  void SetDetails(const std::vector<std::pair<int, double>>& data) {
    for (const auto& el : data) {
      Add(el);
    }
  }

  void Add(std::pair<int, double> rec) {
    if (rec.second == 0.0) return;
    auto it = details_.find(rec.first);
    if (it == details_.end()) {
      details_.insert(rec);
      value_ += rec.second;
    } else {
      if (it->second == -rec.second) {
        details_.erase(it);
      } else {
        it->second += rec.second;
        value_ += rec.second;
      }
    }
  }

  double GetValue(int id) const {
    auto it = details_.find(id);
    return it == details_.end() ? 0.0 : it->second;
  }

  double GetValue() const { return value_; }

 private:
  time_t timestamp_;
  double value_ = 0.0;
  std::map<int, double> details_;
};

class UnorderedMapReturnDataPoint {
 public:
  explicit UnorderedMapReturnDataPoint(time_t t) : timestamp_(t) {}

  void SetDetails(const std::vector<std::pair<int, double>>& data) {
    for (const auto& el : data) {
      Add(el);
    }
  }

  void Add(std::pair<int, double> rec) {
    if (rec.second == 0.0) return;
    auto it = details_.find(rec.first);
    if (it == details_.end()) {
      details_.insert(rec);
      value_ += rec.second;
    } else {
      if (it->second == -rec.second) {
        details_.erase(it);
      } else {
        it->second += rec.second;
        value_ += rec.second;
      }
    }
  }

  double GetValue(int id) const {
    auto it = details_.find(id);
    return it == details_.end() ? 0.0 : it->second;
  }

  double GetValue() const { return value_; }

 private:
  time_t timestamp_;
  double value_ = 0.0;
  std::unordered_map<int, double> details_;
};

class VectorReturnDataPoint {
 public:
  static void AccumulateSortedRealizedInPlace(
      std::vector<std::pair<int, double>>& data) {
    if (data.empty()) return;
    auto last_val = data.begin();
    auto curr_it = last_val;
    while (++curr_it != data.end()) {
      if (last_val->first == curr_it->first) {
        last_val->second += curr_it->second;
      } else {
        if (++last_val != curr_it) {
          *last_val = *curr_it;
        }
      }
    }
    data.erase(++last_val, data.end());
  }

  static void PrepareDetails(std::vector<std::pair<int, double>>& data) {
    std::sort(data.begin(), data.end());
    AccumulateSortedRealizedInPlace(data);
  }

  explicit VectorReturnDataPoint(time_t t) : timestamp_(t) {}

  void SetDetails(const std::vector<std::pair<int, double>>& data) {
    value_ = 0.0;
    for (const auto& el : data) {
      if (el.second != 0.0) {
        value_ += el.second;
        details_.push_back(el);
      }
    }
  }

  double GetValue(int id) const {
    auto it =
        std::lower_bound(details_.begin(), details_.end(), id,
                         [](const auto& p, int id) { return p.first < id; });
    return it == details_.end() ? 0.0 : it->second;
  }

  double GetValue() const { return value_; }

 private:
  time_t timestamp_;
  double value_ = 0.0;
  std::vector<std::pair<int, double>> details_;
};

std::vector<std::pair<int, double>> GenerateData(int size, int random_range) {
  std::mt19937 rnd(std::time(nullptr));
  std::uniform_int_distribution<int> i_dist{0, random_range};
  std::uniform_real_distribution<double> d_dist(0, random_range);
  std::vector<std::pair<int, double>> ret;
  ret.reserve(size);
  std::generate_n(std::back_inserter(ret), size,
                  [&]() { return std::make_pair(i_dist(rnd), d_dist(rnd)); });
  return ret;
}

static void GenerateDataBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::pair<int, double>> data =
        GenerateData(state.range(0), state.range(1));
    benchmark::DoNotOptimize(data);
  }
}

static void MapDetailsBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::pair<int, double>> data =
        GenerateData(state.range(0), state.range(1));
    MapReturnDataPoint test(data.front().first);
    // Inserting
    test.SetDetails(data);
    // Get each value
    double total_value = test.GetValue();
    benchmark::DoNotOptimize(total_value);
    for (const auto& el : data) {
      double id_value = test.GetValue(el.first);
      benchmark::DoNotOptimize(id_value);
    }
  }
}

static void UnorderedMapDetailsBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::pair<int, double>> data =
        GenerateData(state.range(0), state.range(1));
    UnorderedMapReturnDataPoint test(data.front().first);
    // Inserting
    test.SetDetails(data);
    // Get each value
    double total_value = test.GetValue();
    benchmark::DoNotOptimize(total_value);
    for (const auto& el : data) {
      double id_value = test.GetValue(el.first);
      benchmark::DoNotOptimize(id_value);
    }
  }
}

static void VectorDetailsBM(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<std::pair<int, double>> data =
        GenerateData(state.range(0), state.range(1));
    VectorReturnDataPoint test(data.front().first);
    // Inserting
    test.SetDetails(data);
    // Get each value
    double total_value = test.GetValue();
    benchmark::DoNotOptimize(total_value);
    for (const auto& el : data) {
      double id_value = test.GetValue(el.first);
      benchmark::DoNotOptimize(id_value);
    }
  }
}

void GenerateCaseParameters(benchmark::internal::Benchmark* b) {
  std::vector<int64_t> values{10, 50, 100, 500, 1000, 5000};
  b->ArgsProduct({values, values});
}

BENCHMARK(GenerateDataBM)->Apply(GenerateCaseParameters);
BENCHMARK(MapDetailsBM)->Apply(GenerateCaseParameters);
BENCHMARK(UnorderedMapDetailsBM)->Apply(GenerateCaseParameters);
BENCHMARK(VectorDetailsBM)->Apply(GenerateCaseParameters);

BENCHMARK_MAIN();