#include <benchmark/benchmark.h>

#include <armadillo>
#include <limits>
#include <random>
#include <vector>

// Model of current LatestBars realization
class Current {
 public:
  Current(const arma::vec& input) : data_(input) {}

  void ShiftAndWrite(double val) {
    data_ = arma::shift(data_, -1);
    data_.back() = val;
  }

  const arma::vec& GetData() const { return data_; }

 private:
  arma::vec data_;
};

// Version with shifting in place
class InPlaceShift {
 public:
  InPlaceShift(const arma::vec& input) : data_(input) {}

  void ShiftAndWrite(double val) {
    std::rotate(data_.begin(), data_.begin() + data_.size() - 1, data_.end());
    data_.back() = val;
  }

  const arma::vec& GetData() const { return data_; }

 private:
  arma::vec data_;
};

// Perform shift only when it is required
class ShiftOnDemand {
 public:
  ShiftOnDemand(const arma::vec& input) : data_(input) {}

  void ShiftAndWrite(double val) {
    data_[begin_idx_] = val;
    begin_idx_ = Next(begin_idx_);
  }

  const arma::vec& GetData() {
    Flatten();
    return data_;
  }

 private:
  void Flatten() {
    std::rotate(data_.begin(), data_.begin() + begin_idx_, data_.end());
    begin_idx_ = 0;
  }

  size_t Next(size_t pos) const {
    ++pos;
    return pos == data_.size() ? 0 : pos;
  }

  arma::vec data_;
  size_t begin_idx_ = 0;
};

static void BM_Current(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  Current latest_bars(std::move(input));

  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(dist(rnd));
    if (!(index % state.range(1))) {
      double x = latest_bars.GetData()[0];
      benchmark::DoNotOptimize(x);
    }
  }
}

static void BM_InPlaceShift(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  InPlaceShift latest_bars(std::move(input));

  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(dist(rnd));
    if (!(index % state.range(1))) {
      double x = latest_bars.GetData()[0];
      benchmark::DoNotOptimize(x);
    }
  }
}

static void BM_ShiftOnDemand(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  ShiftOnDemand latest_bars(std::move(input));

  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(dist(rnd));
    if (!(index % state.range(1))) {
      double x = latest_bars.GetData()[0];
      benchmark::DoNotOptimize(x);
    }
  }
}

BENCHMARK(BM_Current)->ArgsProduct({{50, 100, 200}, {1, 5, 10, 1000}});
BENCHMARK(BM_InPlaceShift)->ArgsProduct({{50, 100, 200}, {1, 5, 10, 1000}});
BENCHMARK(BM_ShiftOnDemand)->ArgsProduct({{50, 100, 200}, {1, 5, 10, 1000}});

BENCHMARK_MAIN();
