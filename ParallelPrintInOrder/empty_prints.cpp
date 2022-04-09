#include <benchmark/benchmark.h>

#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class FooBarCV {
 private:
  const int num_;
  std::mutex m_;
  std::condition_variable cv_;
  bool need_foo_ = true;
  std::vector<std::string> data_;

 public:
  FooBarCV(int n) : num_(n) { data_.reserve(num_); }

  const std::vector<std::string>& GetData() const { return data_; }

  void WaitPrintFoo() {
    std::unique_lock<std::mutex> lock(m_);
    cv_.wait(lock, [this]() { return !need_foo_; });
  }

  void foo() {
    for (int i = 0; i < num_; i++) {
      std::unique_lock<std::mutex> lock(m_);
      cv_.wait(lock, [this]() { return need_foo_; });
      data_.push_back("foo");
      need_foo_ = false;
      cv_.notify_one();
    }
  }

  void bar() {
    WaitPrintFoo();
    for (int i = 0; i < num_; i++) {
      std::unique_lock<std::mutex> lock(m_);
      cv_.wait(lock, [this]() { return !need_foo_; });
      data_.back().append("bar");
      need_foo_ = true;
      cv_.notify_one();
    }
  }
};

class FooBarDoubleMutex {
 private:
  const int num_;
  std::mutex bar_mutex_;
  std::mutex foo_mutex_;
  std::vector<std::string> data_;

 public:
  FooBarDoubleMutex(int n) : num_(n) {
    data_.reserve(num_);
    bar_mutex_.lock();
  }

  const std::vector<std::string>& GetData() const { return data_; }

  void foo() {
    for (int i = 0; i < num_; i++) {
      foo_mutex_.lock();
      data_.push_back("foo");
      bar_mutex_.unlock();
    }
  }

  void bar() {
    for (int i = 0; i < num_; i++) {
      bar_mutex_.lock();
      data_.back().append("bar");
      foo_mutex_.unlock();
    }
  }
};

static void BM_ConVarThread(benchmark::State& state) {
  for (auto _ : state) {
    FooBarCV test(state.range(0));
    auto lhs = std::thread([&test]() { test.foo(); });
    auto rhs = std::thread([&test]() { test.bar(); });
    lhs.join();
    rhs.join();
    benchmark::DoNotOptimize(test.GetData());
  }
}

static void BM_DoubleMutexThread(benchmark::State& state) {
  for (auto _ : state) {
    FooBarDoubleMutex test(state.range(0));
    auto lhs = std::thread([&test]() { test.foo(); });
    auto rhs = std::thread([&test]() { test.bar(); });
    lhs.join();
    rhs.join();
    benchmark::DoNotOptimize(test.GetData());
  }
}

static void BM_ConVarAsync(benchmark::State& state) {
  for (auto _ : state) {
    FooBarCV test(state.range(0));
    auto lhs = std::async(std::launch::async, &FooBarCV::foo, std::ref(test));
    auto rhs = std::async(std::launch::async, &FooBarCV::bar, std::ref(test));
    lhs.get();
    rhs.get();
    benchmark::DoNotOptimize(test.GetData());
  }
}

static void BM_DoubleMutexAsync(benchmark::State& state) {
  for (auto _ : state) {
    FooBarDoubleMutex test(state.range(0));
    auto lhs =
        std::async(std::launch::async, &FooBarDoubleMutex::foo, std::ref(test));
    auto rhs =
        std::async(std::launch::async, &FooBarDoubleMutex::bar, std::ref(test));
    lhs.get();
    rhs.get();
    benchmark::DoNotOptimize(test.GetData());
  }
}

BENCHMARK(BM_ConVarThread)->Range(10, 10 << 10);
BENCHMARK(BM_ConVarAsync)->Range(10, 10 << 10);
BENCHMARK(BM_DoubleMutexThread)->Range(10, 10 << 10);
BENCHMARK(BM_DoubleMutexAsync)->Range(10, 10 << 10);
