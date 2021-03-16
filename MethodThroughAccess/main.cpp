#include <memory>
#include<string>
#include "benchmark/benchmark.h"

#include "level_1.hpp"
#include "level_2.hpp"
#include "level_3.hpp"


#define ITER_NUM 100000


static void BM_DirectAccess(benchmark::State& state) {
    LhsColl lhs{};
    RhsColl rhs{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(str = lhs.some_string_);
            benchmark::DoNotOptimize(str = lhs.another_string_);
            benchmark::DoNotOptimize(d = lhs.start_);
            benchmark::DoNotOptimize(d = lhs.end_);
            benchmark::DoNotOptimize(d = lhs.smth_);
            benchmark::DoNotOptimize(n = lhs.x_);
            benchmark::DoNotOptimize(n = lhs.y_);
            benchmark::DoNotOptimize(n = lhs.z_);
            benchmark::DoNotOptimize(s = lhs.id_);

            benchmark::DoNotOptimize(str = rhs.some_string_);
            benchmark::DoNotOptimize(str = rhs.another_string_);
            benchmark::DoNotOptimize(d = rhs.start_);
            benchmark::DoNotOptimize(d = rhs.end_);
            benchmark::DoNotOptimize(d = rhs.smth_);
            benchmark::DoNotOptimize(n = rhs.x_);
            benchmark::DoNotOptimize(n = rhs.y_);
            benchmark::DoNotOptimize(n = rhs.z_);
            benchmark::DoNotOptimize(s = rhs.id_);
        }
    }
}




static void BM_FullPath(benchmark::State& state) {
    Config cfg{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(str = cfg.GetInfo()->lhs_.some_string_);
            benchmark::DoNotOptimize(str = cfg.GetInfo()->lhs_.another_string_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.start_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.end_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.smth_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.x_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.y_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.z_);
            benchmark::DoNotOptimize(s = cfg.GetInfo()->lhs_.id_);

            benchmark::DoNotOptimize(str = cfg.GetInfo()->rhs_.some_string_);
            benchmark::DoNotOptimize(str = cfg.GetInfo()->rhs_.another_string_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.start_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.end_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.smth_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.x_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.y_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.z_);
            benchmark::DoNotOptimize(s = cfg.GetInfo()->rhs_.id_);
        }
    }
}



static void BM_FullPathInl(benchmark::State& state) {
    ConfigInl cfg{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            benchmark::DoNotOptimize(str = cfg.GetInfo()->lhs_.some_string_);
            benchmark::DoNotOptimize(str = cfg.GetInfo()->lhs_.another_string_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.start_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.end_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->lhs_.smth_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.x_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.y_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->lhs_.z_);
            benchmark::DoNotOptimize(s = cfg.GetInfo()->lhs_.id_);

            benchmark::DoNotOptimize(str = cfg.GetInfo()->rhs_.some_string_);
            benchmark::DoNotOptimize(str = cfg.GetInfo()->rhs_.another_string_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.start_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.end_);
            benchmark::DoNotOptimize(d = cfg.GetInfo()->rhs_.smth_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.x_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.y_);
            benchmark::DoNotOptimize(n = cfg.GetInfo()->rhs_.z_);
            benchmark::DoNotOptimize(s = cfg.GetInfo()->rhs_.id_);
        }
    }
}


static void BM_BufferSharedPtr(benchmark::State& state) {
    Config cfg{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            const auto& ptr = cfg.GetInfo();
            benchmark::DoNotOptimize(str = ptr->lhs_.some_string_);
            benchmark::DoNotOptimize(str = ptr->lhs_.another_string_);
            benchmark::DoNotOptimize(d = ptr->lhs_.start_);
            benchmark::DoNotOptimize(d = ptr->lhs_.end_);
            benchmark::DoNotOptimize(d = ptr->lhs_.smth_);
            benchmark::DoNotOptimize(n = ptr->lhs_.x_);
            benchmark::DoNotOptimize(n = ptr->lhs_.y_);
            benchmark::DoNotOptimize(n = ptr->lhs_.z_);
            benchmark::DoNotOptimize(s = ptr->lhs_.id_);

            benchmark::DoNotOptimize(str = ptr->rhs_.some_string_);
            benchmark::DoNotOptimize(str = ptr->rhs_.another_string_);
            benchmark::DoNotOptimize(d = ptr->rhs_.start_);
            benchmark::DoNotOptimize(d = ptr->rhs_.end_);
            benchmark::DoNotOptimize(d = ptr->rhs_.smth_);
            benchmark::DoNotOptimize(n = ptr->rhs_.x_);
            benchmark::DoNotOptimize(n = ptr->rhs_.y_);
            benchmark::DoNotOptimize(n = ptr->rhs_.z_);
            benchmark::DoNotOptimize(s = ptr->rhs_.id_);
        }
    }
}





static void BM_ThroughRef(benchmark::State& state) {
    Config cfg{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            const auto& lhs_ = cfg.GetInfo()->lhs_;
            const auto& rhs_ = cfg.GetInfo()->rhs_;
            benchmark::DoNotOptimize(str = lhs_.some_string_);
            benchmark::DoNotOptimize(str = lhs_.another_string_);
            benchmark::DoNotOptimize(d = lhs_.start_);
            benchmark::DoNotOptimize(d = lhs_.end_);
            benchmark::DoNotOptimize(d = lhs_.smth_);
            benchmark::DoNotOptimize(n = lhs_.x_);
            benchmark::DoNotOptimize(n = lhs_.y_);
            benchmark::DoNotOptimize(n = lhs_.z_);
            benchmark::DoNotOptimize(s = lhs_.id_);

            benchmark::DoNotOptimize(str = rhs_.some_string_);
            benchmark::DoNotOptimize(str = rhs_.another_string_);
            benchmark::DoNotOptimize(d = rhs_.start_);
            benchmark::DoNotOptimize(d = rhs_.end_);
            benchmark::DoNotOptimize(d = rhs_.smth_);
            benchmark::DoNotOptimize(n = rhs_.x_);
            benchmark::DoNotOptimize(n = rhs_.y_);
            benchmark::DoNotOptimize(n = rhs_.z_);
            benchmark::DoNotOptimize(s = rhs_.id_);
        }
    }
}


static void BM_ThroughRefInl(benchmark::State& state) {
    ConfigInl cfg{};
    std::string str;
    double d;
    int64_t n;
    size_t s;
    for (auto _ : state) {
        for(size_t i=0; i<state.range(0); i++){
            const auto& lhs_ = cfg.GetInfo()->lhs_;
            const auto& rhs_ = cfg.GetInfo()->rhs_;
            benchmark::DoNotOptimize(str = lhs_.some_string_);
            benchmark::DoNotOptimize(str = lhs_.another_string_);
            benchmark::DoNotOptimize(d = lhs_.start_);
            benchmark::DoNotOptimize(d = lhs_.end_);
            benchmark::DoNotOptimize(d = lhs_.smth_);
            benchmark::DoNotOptimize(n = lhs_.x_);
            benchmark::DoNotOptimize(n = lhs_.y_);
            benchmark::DoNotOptimize(n = lhs_.z_);
            benchmark::DoNotOptimize(s = lhs_.id_);

            benchmark::DoNotOptimize(str = rhs_.some_string_);
            benchmark::DoNotOptimize(str = rhs_.another_string_);
            benchmark::DoNotOptimize(d = rhs_.start_);
            benchmark::DoNotOptimize(d = rhs_.end_);
            benchmark::DoNotOptimize(d = rhs_.smth_);
            benchmark::DoNotOptimize(n = rhs_.x_);
            benchmark::DoNotOptimize(n = rhs_.y_);
            benchmark::DoNotOptimize(n = rhs_.z_);
            benchmark::DoNotOptimize(s = rhs_.id_);
        }
    }
}





// Register the function as a benchmark
BENCHMARK(BM_DirectAccess)->Arg(ITER_NUM);
BENCHMARK(BM_FullPath)->Arg(ITER_NUM);
BENCHMARK(BM_BufferSharedPtr)->Arg(ITER_NUM);
BENCHMARK(BM_FullPathInl)->Arg(ITER_NUM);
BENCHMARK(BM_ThroughRef)->Arg(ITER_NUM);
BENCHMARK(BM_ThroughRefInl)->Arg(ITER_NUM);
// Run the benchmark
BENCHMARK_MAIN();
