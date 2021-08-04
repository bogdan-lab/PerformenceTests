#ifndef LOGGER_SEPARATE_FLUSH_H
#define LOGGER_SEPARATE_FLUSH_H

#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
#include <utility>

class LoggerSeparateFlush {
 private:
  std::thread flush_thread_;
  std::mutex save_mutex_;
  std::ofstream fout_;
  std::atomic<bool> run_flag_;

 public:
  LoggerSeparateFlush() = delete;
  LoggerSeparateFlush(const std::string& fname) : fout_(fname) {
    run_flag_ = true;
    flush_thread_ = std::thread([this]() {
      auto period = std::chrono::milliseconds(200);
      while (run_flag_) {
        {
          std::lock_guard<std::mutex> lk(save_mutex_);
          fout_.flush();
        }
        std::this_thread::sleep_for(period);
      }
    });
  }

  template <typename ValueType>
  LoggerSeparateFlush& operator<<(ValueType value) {
    fout_ << value;
    return *this;
  }

  ~LoggerSeparateFlush() {
    run_flag_ = false;
    flush_thread_.join();
  }
};

#endif  // LOGGER_SEPARATE_FLUSH_H
