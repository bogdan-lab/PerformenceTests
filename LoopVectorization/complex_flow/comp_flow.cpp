#include <vector>
#include <stdexcept>
#include <algorithm>

enum class Flag{
    GOOD,
    BAD
};


int f_cont(std::vector<int> vec, Flag fg){ 	//NOT!
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        switch (fg) {
        case Flag::GOOD:
            sum += vec[i];
            break;
        case Flag::BAD:
            sum -= vec[i];
            break;
        default:
            break;
        }
    }
    return sum;
}

int f_cont_fixed(std::vector<int> vec, Flag fg){ 	//vector
    int sum = 0;
    switch (fg) {
    case Flag::GOOD:
        for(size_t i=0; i<vec.size(); i++) sum+= vec[i];
        break;
    case Flag::BAD:
        for(size_t i=0; i<vec.size(); i++) sum-= vec[i];
        break;
    default:
        break;
    }
    return sum;
}



int f_dep_if(std::vector<int> vec, int val){ 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        if(0<val) sum+=vec[i];
        else sum -= vec[i];
    }
    return sum;
}


int f_dep_if_2(std::vector<int> vec, int val){ 	//NOT
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]<val) sum+=vec[i];
        else sum -= vec[i];
    }
    return sum;
}

int f_dep_if_2_fixed(std::vector<int> vec, int val){ 	//vector
    auto itLessEnd = std::partition(vec.begin(), vec.end(), [=](int el){
        return el<val;});
    int sum = 0;
    for(auto it=vec.begin(); it!=itLessEnd; it++){
        sum += *it;
    }
    for(auto it=itLessEnd; it!=vec.end(); it++){
        sum -= *it;
    }
    return sum;
}
