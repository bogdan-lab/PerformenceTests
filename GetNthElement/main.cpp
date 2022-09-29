#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <memory>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "benchmark/benchmark.h"

constexpr int kMaxYearValue = 9999;

struct Date {
  int Day;
  int Year;
  int Month;
};

std::vector<Date> GenerateDates(std::mt19937& rnd, int total_num,
                                int dupl_each) {
  int to_gen = total_num / dupl_each;
  std::uniform_int_distribution<int> day_dist{1, 31};
  std::uniform_int_distribution<int> month_dist{1, 12};
  std::uniform_int_distribution<int> year_dist{0, kMaxYearValue};
  std::vector<Date> result;
  result.reserve(total_num + 3);
  // In task we guarantee that there are at least 3 distinct dates
  result.push_back({1, 1, 1});
  result.push_back({1, 1, 2});
  result.push_back({1, 1, 3});
  while (to_gen--) {
    Date d{day_dist(rnd), year_dist(rnd), month_dist(rnd)};
    for (int i = 0; i < dupl_each; ++i) {
      result.push_back(d);
    }
  }
  std::shuffle(result.begin(), result.end(), rnd);
  return result;
}

static void GenerateDatesBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> res = GenerateDates(rnd, state.range(0), state.range(1));
  }
}

Date ThirdLatestAlgoSort(std::vector<Date>& dates) {
  std::sort(dates.begin(), dates.end(), [](const Date& lhs, const Date& rhs) {
    return std::tie(lhs.Year, lhs.Month, lhs.Day) <
           std::tie(rhs.Year, rhs.Month, rhs.Day);
  });
  auto u_end = std::unique(
      dates.begin(), dates.end(), [](const Date& lhs, const Date& rhs) {
        return lhs.Year == rhs.Year && lhs.Month == rhs.Month &&
               lhs.Day == rhs.Day;
      });
  assert(u_end - dates.begin() >= 3);
  return *(u_end - 3);
}

static void AlgoSortBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestAlgoSort(dates);
    benchmark::DoNotOptimize(res);
  }
}

template <typename Func>
void CountSortInplace(std::vector<Date>& dates, int max_size, Func get_val) {
  std::vector<int> count(max_size);
  for (const auto& el : dates) {
    ++count[get_val(el)];
  }
  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i - 1];
  }
  std::vector<int> permut(dates.size());
  for (size_t i = dates.size(); i > 0; --i) {
    size_t curr_pos = i - 1;
    permut[curr_pos] = --count[get_val(dates[curr_pos])];
  }

  size_t index = 0;
  size_t placed_count = 0;
  while (placed_count < dates.size()) {
    // i - current pos, permut[i] - needed pos
    // permut[i] == -1 - this position is already replaced
    if (index == permut[index]) {
      ++placed_count;
    } else if (permut[index] >= 0) {
      size_t curr_pos = index;
      Date moved_date = dates[curr_pos];
      while (permut[curr_pos] >= 0) {
        std::swap(moved_date, dates[permut[curr_pos]]);
        curr_pos = std::exchange(permut[curr_pos], -1);
        ++placed_count;
      }
    }
    ++index;
  }
}

void RadixSortInplace(std::vector<Date>& dates) {
  CountSortInplace(dates, /*max_days=*/32, [](const Date& d) { return d.Day; });
  CountSortInplace(dates, /*max_month=*/13,
                   [](const Date& d) { return d.Month; });
  CountSortInplace(dates, kMaxYearValue + 1,
                   [](const Date& d) { return d.Year; });
}

Date ThirdLatestRadixSortInplace(std::vector<Date>& dates) {
  RadixSortInplace(dates);
  auto u_end = std::unique(
      dates.begin(), dates.end(), [](const Date& lhs, const Date& rhs) {
        return lhs.Year == rhs.Year && lhs.Month == rhs.Month &&
               lhs.Day == rhs.Day;
      });
  assert(u_end - dates.begin() >= 3);
  return *(u_end - 3);
}

static void RadixSortInplaceBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestRadixSortInplace(dates);
    benchmark::DoNotOptimize(res);
  }
}

template <typename Func>
void CountSort(std::vector<Date>& dates, int max_size, Func get_val) {
  std::vector<int> count(max_size);
  for (const auto& el : dates) {
    ++count[get_val(el)];
  }
  for (size_t i = 1; i < count.size(); ++i) {
    count[i] += count[i - 1];
  }
  std::vector<Date> new_dates(dates.size(), {0, 0, 0});
  for (size_t i = dates.size(); i > 0; --i) {
    size_t curr_pos = i - 1;
    new_dates[--count[get_val(dates[curr_pos])]] = dates[curr_pos];
  }
  std::swap(new_dates, dates);
}

void RadixSort(std::vector<Date>& dates) {
  CountSort(dates, /*max_days=*/32, [](const Date& d) { return d.Day; });
  CountSort(dates, /*max_month=*/13, [](const Date& d) { return d.Month; });
  CountSort(dates, kMaxYearValue + 1, [](const Date& d) { return d.Year; });
}

Date ThirdLatestRadixSort(std::vector<Date>& dates) {
  RadixSort(dates);
  auto u_end = std::unique(
      dates.begin(), dates.end(), [](const Date& lhs, const Date& rhs) {
        return lhs.Year == rhs.Year && lhs.Month == rhs.Month &&
               lhs.Day == rhs.Day;
      });
  assert(u_end - dates.begin() >= 3);
  return *(u_end - 3);
}

static void RadixSortBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestRadixSort(dates);
    benchmark::DoNotOptimize(res);
  }
}

constexpr int ToInt(const Date& date) {
  return 10000 * date.Year + 100 * date.Month + date.Day;
}

Date ToDate(int val) {
  int y = val / 10000;
  val -= 10000 * y;
  int m = val / 100;
  val -= 100 * m;
  return {val, y, m};
}

Date ThirdLatestHashMap(std::vector<Date>& dates) {
  std::unordered_set<int> filter;
  filter.reserve(dates.size());
  for (const auto& el : dates) {
    filter.insert(ToInt(el));
  }
  std::vector<int> unique;
  unique.reserve(filter.size());
  for (const auto& el : filter) {
    unique.push_back(el);
  }
  assert(unique.size() >= 3);
  std::nth_element(unique.begin(), unique.end() - 3, unique.end());
  return ToDate(*(unique.end() - 3));
}

static void HashMapBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestHashMap(dates);
    benchmark::DoNotOptimize(res);
  }
}

Date ThirdLatestAlgoSortCompressed(std::vector<Date>& dates) {
  std::vector<int> compresssed;
  compresssed.reserve(dates.size());
  for (const auto& el : dates) {
    compresssed.push_back(ToInt(el));
  }
  std::sort(compresssed.begin(), compresssed.end());
  auto u_end = std::unique(compresssed.begin(), compresssed.end());
  assert(u_end - compresssed.begin() >= 3);
  return ToDate(*(u_end - 3));
}

static void AlgoSortCompressedBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestAlgoSortCompressed(dates);
    benchmark::DoNotOptimize(res);
  }
}

constexpr int kMaxCompressedValue = ToInt({31, kMaxYearValue, 12});

Date ThirdLatestBitSet(std::vector<Date>& dates) {
  auto mp = std::make_unique<std::bitset<kMaxCompressedValue + 1>>();
  int max_val = 0;
  for (const auto& el : dates) {
    int curr_val = ToInt(el);
    mp->set(curr_val);
    max_val = std::max(curr_val, max_val);
  }
  int count = 1;
  int index = max_val;
  while (index > 0) {
    if (mp->test(index - 1)) {
      ++count;
    }
    if (count == 3) break;
    --index;
  }
  return ToDate(index - 1);
}

static void BitSetBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestBitSet(dates);
    benchmark::DoNotOptimize(res);
  }
}

constexpr uint32_t BitCompress(Date d) {
  uint32_t res = 0;
  res |= (d.Year << 9);
  res |= (d.Month << 5);
  res |= d.Day;
  return res;
}

Date BitDecompress(uint32_t val) {
  Date res{0, 0, 0};
  res.Year = (val >> 9);
  val %= (1 << 9);
  res.Month = (val >> 5);
  res.Day = val % (1 << 5);
  return res;
}

Date ThirdLatestBitSetBitCompressed(std::vector<Date>& dates) {
  auto mp = std::make_unique<std::bitset<BitCompress({31, 9999, 12}) + 1>>();
  uint32_t max_val = 0;
  for (const auto& el : dates) {
    uint32_t curr_val = BitCompress(el);
    mp->set(curr_val);
    max_val = std::max(curr_val, max_val);
  }
  int count = 1;
  int index = max_val;
  while (index > 0) {
    if (mp->test(index - 1)) {
      ++count;
    }
    if (count == 3) break;
    --index;
  }
  return BitDecompress(index - 1);
}

static void BitSetBitCompressedBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestBitSetBitCompressed(dates);
    benchmark::DoNotOptimize(res);
  }
}

void PrepareArguments(benchmark::internal::Benchmark* b) {
  std::vector<int> sizes{10, 100, 1000, 10'000, 100'000, 1000'000};
  std::vector<int> duplicates{1, 2, 10, 50, 500, 5000, 50'000, 500'000};
  for (size_t i = 0; i < sizes.size(); ++i) {
    for (size_t j = 0; j < duplicates.size(); ++j) {
      if (duplicates[j] < sizes[i]) {
        b->ArgPair(sizes[i], duplicates[j]);
      }
    }
  }
  b->ArgPair(10'000'000, 1);
  b->ArgPair(10'000'000, 2);
  b->ArgPair(10'000'000, 10);
  b->ArgPair(10'000'000, 50);
  b->ArgPair(100'000'000, 1);
}

Date ThirdLatestBubbleSort(std::vector<Date>& dates) {
  std::vector<uint32_t> compressed;
  compressed.reserve(dates.size());
  for (const auto& el : dates) {
    compressed.push_back(BitCompress(el));
  }
  int8_t count = 1;
  std::swap(*std::max_element(compressed.begin(), compressed.end()),
            compressed.back());

  auto last = std::prev(compressed.end());
  while (count < 3) {
    auto it = std::max_element(compressed.begin(), last);
    count += (*it != *last);
    --last;
    std::swap(*it, *last);
  }
  return BitDecompress(*last);
}

static void BubbleSortBM(benchmark::State& state) {
  std::mt19937 rnd(42);
  for (auto _ : state) {
    std::vector<Date> dates =
        GenerateDates(rnd, state.range(0), state.range(1));
    Date res = ThirdLatestBubbleSort(dates);
    benchmark::DoNotOptimize(res);
  }
}

BENCHMARK(GenerateDatesBM)->Apply(PrepareArguments);
BENCHMARK(AlgoSortBM)->Apply(PrepareArguments);
BENCHMARK(AlgoSortCompressedBM)->Apply(PrepareArguments);
BENCHMARK(BubbleSortBM)->Apply(PrepareArguments);
BENCHMARK(RadixSortInplaceBM)->Apply(PrepareArguments);
BENCHMARK(RadixSortBM)->Apply(PrepareArguments);
BENCHMARK(HashMapBM)->Apply(PrepareArguments);
BENCHMARK(BitSetBM)->Apply(PrepareArguments);
BENCHMARK(BitSetBitCompressedBM)->Apply(PrepareArguments);

BENCHMARK_MAIN();

// TODO Fix bitset solution using permutation