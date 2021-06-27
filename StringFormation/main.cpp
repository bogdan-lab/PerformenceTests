#include <benchmark/benchmark.h>
#include <fmt/core.h>

#include <ctime>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

double generate_double() {
  std::mt19937 rnd(time(0));
  std::uniform_real_distribution<double> dbl_dist{-6.0e9, 6.0e9};
  return dbl_dist(rnd);
}

int generate_int() {
  std::mt19937 rnd(time(0));
  std::uniform_int_distribution<int> int_dist{-1000, 1000};
  return int_dist(rnd);
}

std::string generate_string(size_t length = 50) {
  std::string res;
  std::mt19937 rnd(time(0));
  std::uniform_int_distribution<uint8_t> char_dist{65, 125};
  for (size_t i = 0; i < length; ++i) {
    res.push_back(static_cast<char>(char_dist(rnd)));
  }
  return res;
}

std::string FormatStrinStream(const std::string& str, int val_int,
                              double val_dbl) {
  std::stringstream ss;
  ss << str << " " << val_dbl << " " << val_int << "\n";
  return ss.str();
}

static void BM_StringStream(benchmark::State& state) {
  int val_int = generate_int();
  double val_dbl = generate_double();
  std::string str = generate_string();
  for (auto _ : state) {
    std::string res = FormatStrinStream(str, val_int, val_dbl);
    benchmark::DoNotOptimize(res);
  }
}

std::string FormatAppend(const std::string& str, int val_int, double val_dbl) {
  std::string res;
  return res.append(str)
      .append(" ")
      .append(std::to_string(val_dbl))
      .append(" ")
      .append(std::to_string(val_int))
      .append("\n");
}

static void BM_Append(benchmark::State& state) {
  int val_int = generate_int();
  double val_dbl = generate_double();
  std::string str = generate_string();
  for (auto _ : state) {
    std::string res = FormatAppend(str, val_int, val_dbl);
    benchmark::DoNotOptimize(res);
  }
}

std::string FormatPlus(const std::string& str, int val_int, double val_dbl) {
  return str + " " + std::to_string(val_dbl) + " " + std::to_string(val_int) +
         "\n";
}

static void BM_Plus(benchmark::State& state) {
  int val_int = generate_int();
  double val_dbl = generate_double();
  std::string str = generate_string();
  for (auto _ : state) {
    std::string res = FormatPlus(str, val_int, val_dbl);
    benchmark::DoNotOptimize(res);
  }
}

std::string FormatSprintf(const std::string& str, int val_int, double val_dbl) {
  const size_t buff_size = 1024;
  std::string res;
  res.resize(buff_size);
  std::snprintf(res.data(), buff_size, "%s %g %i\n", str.c_str(), val_dbl,
                val_int);
  return res;
}

static void BM_Sprintf(benchmark::State& state) {
  int val_int = generate_int();
  double val_dbl = generate_double();
  std::string str = generate_string();
  for (auto _ : state) {
    std::string res = FormatSprintf(str, val_int, val_dbl);

    benchmark::DoNotOptimize(res);
  }
}

static void BM_Format(benchmark::State& state) {
  int val_int = generate_int();
  double val_dbl = generate_double();
  std::string str = generate_string();
  for (auto _ : state) {
    std::string res = fmt::format("{} {} {}\n", str, val_dbl, val_int);
    benchmark::DoNotOptimize(res);
  }
}

// Register the function as a benchmark
BENCHMARK(BM_StringStream);
BENCHMARK(BM_Append);
BENCHMARK(BM_Plus);
BENCHMARK(BM_Sprintf);
BENCHMARK(BM_Format);

// Run the benchmark
BENCHMARK_MAIN();
