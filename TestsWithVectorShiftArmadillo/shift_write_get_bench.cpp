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

  arma::vec& GetData() { return data_; }

  double HackGetElement(uint64_t idx) const {
    return data_[idx % data_.size()];
  }

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

  arma::vec& GetData() { return data_; }

  double HackGetElement(uint64_t idx) const {
    return data_[idx % data_.size()];
  }

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

  arma::vec& GetData() {
    Flatten();
    return data_;
  }

  double HackGetElement(uint64_t idx) const {
    return data_[idx % data_.size()];
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

class ShiftOnDemandArma {
 public:
  ShiftOnDemandArma(const arma::vec& input) : data_(input) {}

  void ShiftAndWrite(double val) {
    data_[begin_idx_] = val;
    begin_idx_ = Next(begin_idx_);
  }

  arma::vec& GetData() {
    Flatten();
    return data_;
  }

  double HackGetElement(uint64_t idx) const {
    return data_[idx % data_.size()];
  }

 private:
  void Flatten() {
    data_ = arma::shift(data_, -begin_idx_);
    begin_idx_ = 0;
  }

  int Next(int pos) const {
    ++pos;
    return pos == data_.size() ? 0 : pos;
  }

  arma::vec data_;
  int begin_idx_ = 0;
};

static void BM_Current(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  Current latest_bars(std::move(input));
  uint64_t request_count = state.range(1) > state.range(0)
                               ? std::numeric_limits<uint64_t>::max()
                               : state.range(1);
  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(latest_bars.HackGetElement(index));
    if (!(index % request_count)) {
      benchmark::DoNotOptimize(latest_bars.GetData());
    }
    ++index;
  }
}

static void BM_InPlaceShift(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  InPlaceShift latest_bars(std::move(input));

  uint64_t request_count = state.range(1) > state.range(0)
                               ? std::numeric_limits<uint64_t>::max()
                               : state.range(1);
  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(latest_bars.HackGetElement(index));
    if (!(index % request_count)) {
      benchmark::DoNotOptimize(latest_bars.GetData());
    }
    ++index;
  }
}

static void BM_ShiftOnDemand(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  ShiftOnDemand latest_bars(std::move(input));

  uint64_t request_count = state.range(1) > state.range(0)
                               ? std::numeric_limits<uint64_t>::max()
                               : state.range(1);
  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(latest_bars.HackGetElement(index));
    if (!(index % request_count)) {
      benchmark::DoNotOptimize(latest_bars.GetData());
    }
    ++index;
  }
}

static void BM_ShiftOnDemandArma(benchmark::State& state) {
  std::mt19937 rnd(42);
  std::uniform_real_distribution<double> dist{
      std::numeric_limits<double>::max(), std::numeric_limits<double>::min()};
  arma::vec input(state.range(0));
  std::generate(input.begin(), input.end(), [&]() { return dist(rnd); });

  ShiftOnDemandArma latest_bars(std::move(input));

  uint64_t request_count = state.range(1) > state.range(0)
                               ? std::numeric_limits<uint64_t>::max()
                               : state.range(1);
  uint64_t index = 1;
  for (auto _ : state) {
    latest_bars.ShiftAndWrite(latest_bars.HackGetElement(index));
    if (!(index % request_count)) {
      benchmark::DoNotOptimize(latest_bars.GetData());
    }
    ++index;
  }
}

BENCHMARK(BM_Current)->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10}});
BENCHMARK(BM_InPlaceShift)->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10}});
BENCHMARK(BM_ShiftOnDemand)->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10}});
BENCHMARK(BM_ShiftOnDemandArma)->ArgsProduct({{50, 100, 200}, {1, 2, 5, 10}});

BENCHMARK_MAIN();
