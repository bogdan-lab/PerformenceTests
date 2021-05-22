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
  bool run_flag_;

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

  // TODO without mutex operation creates race condition!!!! fix it
  void LogLine(const std::string& line) { fout_ << line << '\n'; }
  std::ofstream& AccessFout() { return fout_; }

  ~LoggerSeparateFlush() {
    run_flag_ = false;
    flush_thread_.join();
  }
};

#endif  // LOGGER_SEPARATE_FLUSH_H
