#ifndef BUFF_ACC_THREADING_H
#define BUFF_ACC_THREADING_H

#include <atomic>
#include <chrono>
#include <fstream>
#include <mutex>
#include <thread>
#include <vector>

class FastFile {
 private:
  std::chrono::milliseconds flush_period_{200};
  std::ofstream fout_;
  std::vector<std::string> buffer_;
  std::vector<std::string> accumulator_;
  std::mutex flush_mtx_;
  std::thread flush_thread_;
  std::atomic<bool> run_flag_{true};

  void FlushAndClearBuffer() {
    for (const auto& el : buffer_) {
      fout_ << el;
    }
    buffer_.clear();
  }

 public:
  FastFile(const std::string& fname) : fout_(fname) {
    if (!fout_.is_open()) {
      // DO SOMETHING!!!!
    }
    flush_thread_ = std::thread([&]() {
      while (run_flag_) {
        {
          std::lock_guard<std::mutex> lk{flush_mtx_};
          buffer_.swap(accumulator_);
        }
        FlushAndClearBuffer();
        // TODO NO THE REAL PERIOD IS NOT THE SAME AS I SET!
        std::this_thread::sleep_for(flush_period_);
      }
    });
  }

  ~FastFile() {
    run_flag_ = false;
    flush_thread_.join();
    buffer_.swap(accumulator_);
    FlushAndClearBuffer();
  }

  FastFile& SetFlushPeriod(std::chrono::milliseconds period) {
    flush_period_ = period;
    return *this;
  }

  template <typename ValueType>
  FastFile& operator<<(ValueType value) {
    std::lock_guard<std::mutex> lk{flush_mtx_};
    accumulator_.push_back(std::to_string(value));
    return *this;
  }
  FastFile& operator<<(const char* value) {
    std::lock_guard<std::mutex> lk{flush_mtx_};
    accumulator_.emplace_back(value);
    return *this;
  }
  FastFile& operator<<(char value) {
    std::lock_guard<std::mutex> lk{flush_mtx_};
    accumulator_.emplace_back(1, value);
    return *this;
  }
  FastFile& operator<<(std::string value) {
    std::lock_guard<std::mutex> lk{flush_mtx_};
    accumulator_.push_back(std::move(value));
    return *this;
  }
};

#endif  // BUFF_ACC_THREADING_H
