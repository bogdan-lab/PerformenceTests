#include <vector>
#include <numeric>

int f_no_dep(std::vector<int> x){
    int sum = 0;
    for(size_t i=1; i<x.size()-1; i++){
        sum+=x[i];
    }
    return sum;
}


int f_close_fwd(std::vector<int> x){
    int sum = 0;
    for(size_t i=0; i<x.size()-1; i++){
        x[i] = (x[i] + x[i+1])/2;
        sum+=x[i];
    }
    return sum;
}

int f_close_bwd(std::vector<int> x){
    int sum = 0;
    for(size_t i=1; i<x.size(); i++){
        x[i] = (x[i-1]+x[i])/2;
        sum+=x[i];
    }
    return sum;
}

int f_replace_one_val(std::vector<int> x){
    std::vector<int> val;
    val.reserve(x.size());
    for(size_t i=1; i<x.size()-1; i++){
        val.insert(val.begin(), (x[i-1]+x[i]+x[i+1])/3);
    }
    return val.back();

}

int f_close_bwd_SEP(std::vector<int> x){
    for(size_t i=1; i<x.size(); i++){
        x[i] = (x[i-1]+x[i])/2;
    }
    int sum = std::accumulate(x.begin(), x.end(), 0);
    return sum;
}


int f_far_fwd(std::vector<int> x, size_t step){
    int sum = 0;
    for(size_t i=0; i<x.size()-step; i++){
        x[i] = (x[i] + x[i+step])/2;
        sum+=x[i];
    }
    return sum;
}


int f_far_bwd(std::vector<int> x, size_t step){
    int sum = 0;
    for(size_t i=step; i<x.size(); i++){
        x[i] = (x[i-step]+x[i])/2;
        sum+=x[i];
    }
    return sum;
}

