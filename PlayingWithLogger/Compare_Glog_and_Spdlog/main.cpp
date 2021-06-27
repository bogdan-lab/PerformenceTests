#include <QApplication>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "glog/logging.h"
#include "log_widget.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int RunLogger(int argc, char* argv[]) {
  QApplication a(argc, argv);
  LogWidget logObj;
  logObj.AddText("Hello World!\n");
  logObj << "IntValues = " << 1 << " ; " << 2 << '\n';
  logObj << "DoubleValues = " << 3.14 << " ; " << 9.8 << '\n';
  logObj.show();
  return a.exec();
}
/*
auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

void error_handle_example() {
  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_error_handler([](const std::string& msg) {
    spdlog::get("basic_logger")->error("THIS IS ERROR MSG {}", msg);
  });
  console->info("some invalid message to trigger an error {}{}{}{}", 3);
  int x = 10;
  while (x--) {
    console->info("I continue working {}", x);
  }
}
*/

int64_t LogSpdLog(const char* fname, size_t num) {
  std::mt19937 rnd{time(0)};
  std::uniform_real_distribution<double> dist_dbl{-1e4, 1e4};
  std::uniform_int_distribution<int> dist_int{-10000, 10000};
  int rnd_int = dist_int(rnd);
  int rnd_dbl = dist_dbl(rnd);
  spdlog::set_pattern("%v");
  auto logger = spdlog::basic_logger_st("logger", fname, true);
  auto start = std::chrono::system_clock::now();
  while (num--) {
    logger->info(
        "This is long log message since I want to be clear. int = {}, double = "
        "{}\n",
        rnd_int, rnd_dbl);
  }
  auto end = std::chrono::system_clock::now();
  spdlog::drop("logger");
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  return duration.count();
}

double get_avg(const std::vector<int64_t>& vec) {
  int64_t sum = std::accumulate(vec.begin(), vec.end(), 0);
  return 1.0 * sum / vec.size();
}

double get_std(const std::vector<int64_t>& vec, double avg) {
  double D = 0;
  for (size_t i = 0; i < vec.size(); ++i) {
    D = (D * i + (vec[i] - avg) * (vec[i] - avg)) / (i + 1);
  }
  return std::sqrt(D);
}

void DoSpdLogTest(size_t log_num, size_t test_num) {
  std::vector<int64_t> spd_res;
  for (size_t i = 0; i < test_num; ++i) {
    spd_res.push_back(LogSpdLog("spd_log_test.txt", log_num));
  }
  double spd_avg = get_avg(spd_res);
  double spd_std = get_std(spd_res, spd_avg);
  std::cout << "SPDLOG = " << spd_avg << "ms +- " << spd_std << "ms\n";
}

int main(int argc, char* argv[]) {
  // error_handle_example();  // EXAMPLE FOR SPDLOG
  const size_t log_num = 1'000'000;
  const size_t test_num = 50;
  DoSpdLogTest(log_num, test_num);
  return 0;
}
