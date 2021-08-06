#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "buff_acc_threading.h"
#include "separated_flush.h"

#define STRINGS_NUM 1'000'00

constexpr auto kFlushPeriod = std::chrono::milliseconds{20};
constexpr auto kDataIncomePeriod = std::chrono::milliseconds{1};

int64_t wait(std::mt19937& rnd, int t_min, int t_max) {
  auto wait_time = std::chrono::milliseconds{kDataIncomePeriod};
  std::this_thread::sleep_for(wait_time);
  std::uniform_int_distribution<int> dist{t_min, t_max};
  return dist(rnd);
}

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
void TestFullString(Logger& log, std::string logger_name) {
  TimeMeasure tm("Test full string " + std::move(logger_name));
  for (size_t i = 0; i < STRINGS_NUM; i++) {
    log << get_next_string();
  }
}

template <typename Logger>
int64_t BusyLog(Logger& log, std::string logger_name) {
  TimeMeasure tm("Busy log test" + std::move(logger_name));
  std::mt19937 rnd{42};
  int64_t sum = 0;
  for (size_t i = 0; i < STRINGS_NUM; i++) {
    sum += wait(rnd, 0, 2);
    log << get_next_string();
  }
  return sum;
}

template <typename Logger>
void TestPartialStrings(Logger& log, std::string logger_name) {
  TimeMeasure tm("Test partial string " + std::move(logger_name));
  for (size_t i = 0; i < STRINGS_NUM; i++) {
    log << 55 << ';' << 23311 << ';' << "DISH" << ';' << "2008-01-03 09:30:00"
        << ';' << "2008-01-03 09:30:00"
        << "MKT" << ';' << 1 << '\n';
  }
}

int main() {
  /*{
    std::ofstream smp_log{"smp_log_busy.txt"};
    auto x = BusyLog(smp_log, "Simple log");
    std::cout << "SUM = " << x << '\n';
  }*/
  {
    LoggerSeparateFlush sep_log("sep_log_busy.txt", kFlushPeriod);
    auto x = BusyLog(sep_log, "Separate flush");
    std::cout << "SUM = " << x << '\n';
  }

  {
    FastFile ff{"fast_file_busy.txt", kFlushPeriod};
    auto x = BusyLog(ff, "Fast file");
    std::cout << "SUM = " << x << '\n';
  }
  return 0;
}
