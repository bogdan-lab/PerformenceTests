#include <algorithm>
#include <random>
#include <vector>
#include <time.h>
#include <cmath>

#include<benchmark/benchmark.h>

static std::mt19937 rnd(0);

double calc_func(double x){
    return std::sqrt(1 - std::sin(x)*std::sin(x));
}

double busy_function(int value, double step = 0.5){
    /*Busy function - simply need it to fill ICache so it should increase
     * the cost of branch miss.
     * */
    int lhs = -std::abs(value);
    int rhs = std::abs(value);
    double x = lhs;
    double integral = 0.0;
    while(x<rhs){
        integral+=0.5*step*(calc_func(x) + calc_func(x+step));
        x+=step;
    }
    return integral ;
}

double busy_function_dep(int value_1, int& value_2, double step=0.5){
    /*This is busy function which will depend on two given parameters
     *and modify one of them. Thus compiler will not be able to vectorize
     * call of this function in the loop*/
    double integral = 0.0;
    int lhs = std::min(value_1, value_2);
    int rhs = std::max(value_1, value_2);
    double x = lhs;
    while(x<rhs){
        integral+=0.5*step*(calc_func(x) + calc_func(x+step));
        x+=step;
    }
    value_2 = (value_1 + value_2)/2;
    return integral;
}


std::vector<int> generate_data(const size_t size){
    std::uniform_int_distribution<int> dist(0, 1000);
    std::vector<int> data;
    data.reserve(size);
    for(size_t i=0; i<size; i++){
        data.push_back(dist(rnd));
    }
    return data;
}


static void Baseline_SimpleInstr(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    double sum = 0;
    for(auto _ : state) {
        benchmark::DoNotOptimize(
            sum = std::accumulate(data.begin(), data.end(), 0.0)
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }

}


static void WithPartition_SimplInstr(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    size_t sum = 0;
    for(auto _ : state) {
        auto it = std::partition(data.begin(), data.end(), [&](const int el){
            return el%state.range(1)==0;});
        benchmark::DoNotOptimize(
            sum = std::accumulate(data.begin(), it, 0)
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }
}


static void NoPartition_SimplInstr(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    std::uniform_int_distribution<int> dist(0, 1000);
    size_t sum = 0;
    for(auto _ : state) {
        sum = 0;
        for(size_t i=0; i<data.size(); i++){
            benchmark::DoNotOptimize(sum += data[i]%state.range(1)==0 ? data[i] : 0);
        }
        std::shuffle(data.begin(), data.end(), rnd);
    }
}
//=========================================================================================
static void Baseline_IND_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    double sum = 0;
    for(auto _ : state) {
        benchmark::DoNotOptimize(
            std::for_each(data.begin(), data.end(), [&](int x){sum += busy_function(x);})
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }

}


static void WithPartition_IND_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    double sum = 0;
    for(auto _ : state) {
        auto it = std::partition(data.begin(), data.end(), [&](const int el){
            return el%state.range(1)==0;});
        benchmark::DoNotOptimize(
            std::for_each(data.begin(), it, [&](int x){sum += busy_function(x);})
        );
        std::shuffle(data.begin(), data.end(), rnd);
    }
}


static void NoPartition_IND_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    std::uniform_int_distribution<int> dist(0, 1000);
    size_t sum = 0;
    for(auto _ : state) {
        sum = 0;
        for(size_t i=0; i<data.size(); i++){
            if(data[i]%state.range(1)==0){
                sum+=busy_function(data[i]);
            }
        }
        std::shuffle(data.begin(), data.end(), rnd);
    }
}

//==================================================================================
static void Baseline_DEP_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    double sum = 0;
    for(auto _ : state) {
        for(size_t i=0; i<data.size()-1; i++){
            sum += busy_function_dep(data[i], data[i+1]);
        }
        std::shuffle(data.begin(), data.end(), rnd);
    }

}


static void WithPartition_DEP_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    double sum = 0;
    for(auto _ : state) {
        auto partEnd = std::partition(data.begin(), data.end(), [&](const int el){
            return el%state.range(1)==0;});
        partEnd = std::prev(partEnd);
        for(auto it=data.begin(); it!=partEnd; it++){
            sum+=busy_function_dep(*it, *std::next(it));
        }
        std::shuffle(data.begin(), data.end(), rnd);
    }
}


static void NoPartition_DEP_BusyFunc(benchmark::State& state){
    std::vector<int> data = generate_data(state.range(0));
    std::uniform_int_distribution<int> dist(0, 1000);
    size_t sum = 0;
    for(auto _ : state) {
        sum = 0;
        for(size_t i=0; i<data.size()-1; i++){
            if(data[i]%state.range(1)==0){
                sum+=busy_function_dep(data[i], data[i+1]);
            }
        }
        std::shuffle(data.begin(), data.end(), rnd);
    }
}

/*Functions with one line instructions - should be cheap branch miss?*/
BENCHMARK(Baseline_SimpleInstr)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(WithPartition_SimplInstr)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(NoPartition_SimplInstr)->ArgsProduct({{1000}, {2, 5, 10, 20}});

/*Functions with many instructions - should be expensive branch miss.
 *However instructions can be vectorized in the loop*/
BENCHMARK(Baseline_IND_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(WithPartition_IND_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(NoPartition_IND_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});

/*Functions with many instructions - should be expensive branch miss.
 *BUT THESE CANNOT BE VECTORIZED!*/
BENCHMARK(Baseline_DEP_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(WithPartition_DEP_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});
BENCHMARK(NoPartition_DEP_BusyFunc)->ArgsProduct({{1000}, {2, 5, 10, 20}});



// Run the benchmark
BENCHMARK_MAIN();
