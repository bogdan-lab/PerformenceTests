#include "source_generator.h"

#include <algorithm>
#include <ctime>
#include <random>

std::vector<std::queue<double>> GenerateSources(int src_num, int src_len) {
  std::mt19937 rnd(std::time(nullptr));
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::vector<std::queue<double>> result;
  result.reserve(src_num);
  while (src_num--) {
    std::vector<double> buff(src_len);
    std::generate(buff.begin(), buff.end(), [&]() { return dist(rnd); });
    std::sort(buff.begin(), buff.end());
    result.emplace_back();
    for (const auto& el : buff) {
      result.back().push(el);
    }
  }
  return result;
}