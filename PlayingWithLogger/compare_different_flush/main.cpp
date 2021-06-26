#include <chrono>
#include <iostream>

#include "separated_flush.h"
#include "simple_logger.h"

#define STRINGS_NUM 1'000'000'0

std::string get_next_string() {
  return "55;23311;DISH;2008-01-03 09:30:00;2008-01-03 "
         "09:30:00;1143856;26.2107;26.2271;18691.6;-1.14386e+06;MKT;1";
}

class TimeMeasure {
  std::string message_;
  const std::chrono::time_point<std::chrono::system_clock> start_;
  std::chrono::time_point<std::chrono::system_clock> end_;

 public:
  TimeMeasure(std::string msg)
      : message_(std::move(msg)), start_(std::chrono::system_clock::now()) {}

  ~TimeMeasure() {
    end_ = std::chrono::system_clock::now();
    std::cout << message_ << " : "
              << std::chrono::duration_cast<std::chrono::microseconds>(end_ -
                                                                       start_)
                     .count()
              << "us\n";
  }
};

int main() {
  /*
    {
      TimeMeasure tm("Separate flush");
      LoggerSeparateFlush sep_log("sep_log.txt");
      for (size_t i = 0; i < STRINGS_NUM; i++) {
        sep_log.LogLine(get_next_string());
      }
    }

    {
      TimeMeasure tm("Simple flush");
      SimpleLogger smp_log("smp_log.txt");
      for (size_t i = 0; i < STRINGS_NUM; i++) {
        smp_log.LogLine(get_next_string());
      }
    }
  */
  {
    TimeMeasure tm("Separate flush");
    LoggerSeparateFlush sep_log("sep_log_partial.txt");
    for (size_t i = 0; i < STRINGS_NUM; i++) {
      sep_log.AccessFout() << 55 << ';' << 23311 << ';' << "DISH" << ';'
                           << "2008-01-03 09:30:00" << ';'
                           << "2008-01-03 09:30:00" << ';' << 1143856 << ';'
                           << ';' << 26.2107 << ';' << 26.2271 << ';' << 18691.6
                           << ';' << -1.14386e+06 << ';' << "MKT" << ';' << 1
                           << '\n';
    }
  }

  {
    TimeMeasure tm("Simple flush");
    SimpleLogger smp_log("smp_log_partial.txt");
    for (size_t i = 0; i < STRINGS_NUM; i++) {
      smp_log.AccessFout() << 55 << ';' << 23311 << ';' << "DISH" << ';'
                           << "2008-01-03 09:30:00" << ';'
                           << "2008-01-03 09:30:00" << ';' << 1143856 << ';'
                           << ';' << 26.2107 << ';' << 26.2271 << ';' << 18691.6
                           << ';' << -1.14386e+06 << ';' << "MKT" << ';' << 1
                           << '\n';
    }
  }
  return 0;
}
