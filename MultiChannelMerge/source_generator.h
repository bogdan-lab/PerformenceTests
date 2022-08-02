#ifndef MULTI_CHANNEL_MERGE_SOURCE_GENERATOR_H
#define MULTI_CHANNEL_MERGE_SOURCE_GENERATOR_H

#include <queue>
#include <random>
#include <vector>

std::vector<std::queue<double>> GenerateSources(int src_num, int src_len);

#endif  // MULTI_CHANNEL_MERGE_SOURCE_GENERATOR_H