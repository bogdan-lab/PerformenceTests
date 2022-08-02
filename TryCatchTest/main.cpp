#include "benchmark/benchmark.h"
#include <algorithm>
#include <random>
#include <string>
#include <deque>
#include <stdexcept>


#define ELEMENT_NUM 10000


class Number{
public:
    virtual int get_value(std::mt19937& rnd) = 0;
};



class LessThanFive : public Number{
private:
    std::uniform_int_distribution<int> dist_;

public:
    LessThanFive() : dist_(0,4) {}

    int get_value(std::mt19937& rnd) override {
        return dist_(rnd);
    }
};



class LargerThanFive : public Number{
private:
    std::uniform_int_distribution<int> dist_;

public:
    LargerThanFive() : dist_(6,10) {}

    int get_value(std::mt19937& rnd) override {
        return dist_(rnd);
    }
};


std::mt19937 rnd(42);


int get_larger_val_ref(Number& num){
    int val = 0;
    try{
        LargerThanFive& gen = dynamic_cast<LargerThanFive&>(num);
        val = gen.get_value(rnd);
    } catch (std::bad_cast& ex){
        val = -1;
    }
    return val;
}


int get_larger_val_ptr(Number* num){
    int val = 0;
    if(LargerThanFive* ptr = dynamic_cast<LargerThanFive*>(num)){
        val = ptr->get_value(rnd);
    } else {
        val = -1;
    }
    return val;
}


std::vector<Number*> generate_vector(size_t el_num, size_t every_nth){
    std::vector<Number*> vec;
    vec.reserve(el_num);
    std::uniform_int_distribution<int> dist(0, 10000);
    for(size_t i=0; i<el_num; i++){
        if (dist(rnd)%every_nth)
            vec.push_back(new LargerThanFive());
        else
            vec.push_back(new LessThanFive());
    }
    return vec;
}


static void BM_if_else_case(benchmark::State& state){
    std::vector<Number*> vec = generate_vector(state.range(0), state.range(1));
    int sum = 0;
    for(auto _ : state){
        for(size_t i=0; i<vec.size(); i++){
            sum += get_larger_val_ptr(vec[i]);
        }
        sum /= state.range(0);
    }
}


static void BM_try_catch_case(benchmark::State& state){
    std::vector<Number*> vec = generate_vector(state.range(0), state.range(1));
    int sum = 0;
    for(auto _ : state){
        for(size_t i=0; i<vec.size(); i++){
            sum += get_larger_val_ref(*vec[i]);
        }
        sum /= state.range(0);
    }
}



// Register the function as a benchmark
BENCHMARK(BM_if_else_case)->ArgsProduct({{ELEMENT_NUM}, {2, 3, 5, 10}});
BENCHMARK(BM_try_catch_case)->ArgsProduct({{ELEMENT_NUM}, {2, 3, 5, 10}});

// Run the benchmark
BENCHMARK_MAIN();
