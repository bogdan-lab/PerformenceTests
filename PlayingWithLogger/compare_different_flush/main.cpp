#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "buff_acc_threading.h"
#include "separated_flush.h"

#define STRINGS_NUM 1'000'000

constexpr auto kFlushPeriod = std::chrono::milliseconds{1000};
constexpr auto kDataIncomePeriod = std::chrono::microseconds{1};

std::string get_next_string() {
  return "55;23311;DISH;2008-01-03 09:30:00;2008-01-03 "
         "09:30:00;1143856;26.2107;26.2271;18691.6;-1.1438;MKT;1\n";
}

class TimeMeasure {
  std::string message_;
  const std::chrono::time_point<std::chrono::steady_clock> start_;

 public:
  TimeMeasure(std::string msg)
      : message_(std::move(msg)), start_(std::chrono::steady_clock::now()) {}

  ~TimeMeasure() {
    auto res = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now() - start_);
    std::cout << message_ << " : \t" << res.count() << "ms\n";
  }
};

template <typename Logger>
void BusyLog(Logger& log, std::string logger_name) {
  TimeMeasure tm("Busy log test" + std::move(logger_name));
  for (size_t i = 0; i < STRINGS_NUM; i++) {
    std::this_thread::sleep_for(kDataIncomePeriod);
    log << get_next_string();
  }
}

int main() {
  {
    std::ofstream smp_log{"smp_log_busy.txt"};
    BusyLog(smp_log, "Simple log");
  }
  {
    LoggerSeparateFlush sep_log("sep_log_busy.txt", kFlushPeriod);
    BusyLog(sep_log, "Separate flush");
  }

  {
    FastFile ff{"fast_file_busy.txt", kFlushPeriod};
    BusyLog(ff, "Fast file");
  }
  return 0;
}
