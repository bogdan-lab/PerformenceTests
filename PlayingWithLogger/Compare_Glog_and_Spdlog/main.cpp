#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "glog/logging.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int64_t LogSpdLog(const char* fname, size_t num) {
  std::mt19937 rnd{time(0)};
  std::uniform_real_distribution<double> dist_dbl{-1e4, 1e4};
  std::uniform_int_distribution<int> dist_int{-10000, 10000};
  int rnd_int = dist_int(rnd);
  double rnd_dbl = dist_dbl(rnd);
  auto logger = spdlog::basic_logger_st("logger", fname, true);
  auto start = std::chrono::system_clock::now();
  while (num--) {
    logger->info(
        "This is long log message since I want to be clear. int = {}, double = "
        "{}",
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

int64_t LogGLog(size_t num) {
  std::mt19937 rnd{time(0)};
  std::uniform_real_distribution<double> dist_dbl{-1e4, 1e4};
  std::uniform_int_distribution<int> dist_int{-10000, 10000};
  int rnd_int = dist_int(rnd);
  double rnd_dbl = dist_dbl(rnd);
  auto start = std::chrono::system_clock::now();
  while (num--) {
    LOG(INFO) << "This is long log message since I want to be clear. int = "
              << rnd_int << ", double = " << rnd_dbl;
  }
  auto end = std::chrono::system_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  return duration.count();
}

void DoGLogTest(size_t log_num, size_t test_num) {
  FLAGS_log_dir = "glog_logs/";
  google::InitGoogleLogging("GoogleLogger");
  std::vector<int64_t> glog_res;
  for (size_t i = 0; i < test_num; ++i) {
    glog_res.push_back(LogGLog(log_num));
  }
  std::vector<int> tmp;
  CHECK_NOTNULL(nullptr);
  std::cout << tmp[0];
  double glog_avg = get_avg(glog_res);
  double glog_std = get_std(glog_res, glog_avg);
  std::cout << "GLOG = " << glog_avg << "ms +- " << glog_std << "ms\n";
}

int main(int argc, char* argv[]) {
  const size_t log_num = 1'000;
  const size_t test_num = 50;
  // DoSpdLogTest(log_num, test_num);
  DoGLogTest(log_num, 1);
  return 0;
}
