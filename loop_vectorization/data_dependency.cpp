#include <vector>

#define LS 3
#define TYPE int

TYPE f_no_dep(std::vector<TYPE> x){
    TYPE sum = 0;
    for(size_t i=0; i<x.size(); i++){
        sum+=x[i];
    }
    return sum;
}


TYPE f_close_fwd(std::vector<TYPE> x){
    TYPE sum = 0;
    for(size_t i=0; i<x.size()-1; i++){
        x[i] = (x[i] + x[i+1])/2;
        sum+=x[i];
    }
    return sum;
}

TYPE f_close_bwd(std::vector<TYPE> x){
    TYPE sum = 0;
    for(size_t i=1; i<x.size(); i++){
        x[i] = (x[i-1]+x[i])/2;
        sum+=x[i];
    }
    return sum;
}


TYPE f_far_fwd(std::vector<TYPE> x, size_t step){
    TYPE sum = 0;
    for(size_t i=0; i<x.size()-step; i++){
        x[i] = (x[i] + x[i+step])/2;
        sum+=x[i];
    }
    return sum;
}


TYPE f_far_bwd(std::vector<TYPE> x, size_t step){
    TYPE sum = 0;
    for(size_t i=step; i<x.size(); i++){
        x[i] = (x[i-step]+x[i])/2;
        sum+=x[i];
    }
    return sum;
}

