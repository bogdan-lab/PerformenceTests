#include <chrono>
#include <iostream>

#include "buff_acc_threading.h"
#include "separated_flush.h"
#include "simple_logger.h"

#define STRINGS_NUM 1'000'000

const char* get_next_string() {
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
void TestPartialStrings(Logger& log, std::string logger_name) {
  TimeMeasure tm("Test partial string " + std::move(logger_name));
  for (size_t i = 0; i < STRINGS_NUM; i++) {
    log << 55 << ';' << 23311 << ';' << "DISH" << ';' << "2008-01-03 09:30:00"
        << ';' << "2008-01-03 09:30:00"
        << "MKT" << ';' << 1 << '\n';
  }
}

int main() {
  {
    SimpleLogger smp_log("smp_log_1.txt");
    TestFullString(smp_log, "Simple log");
  }
  {
    LoggerSeparateFlush sep_log("sep_log_1.txt");
    TestFullString(sep_log, "Separate flush");
  }

  {
    FastFile ff{"fast_file_1.txt"};
    TestFullString(ff, "Fast file");
  }
  {
    SimpleLogger smp_log("smp_log_2.txt");
    TestPartialStrings(smp_log, "Simple log");
  }
  {
    LoggerSeparateFlush sep_log("sep_log_2.txt");
    TestPartialStrings(sep_log, "Separate flush");
  }

  {
    FastFile ff{"fast_file_2.txt"};
    TestPartialStrings(ff, "Fast file");
  }
  return 0;
}
