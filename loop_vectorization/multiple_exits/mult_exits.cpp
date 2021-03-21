#include <vector>
#include <stdexcept>





int f_cont(std::vector<int> vec, int val){
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]==val) continue;
        sum += vec[i];
    }
    return sum;
}




int f_break(std::vector<int> vec, int val){
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]==val) break;
        sum += vec[i];
    }
    return sum;
}

int f_throw(std::vector<int> vec, int val){
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        if(vec[i]==val) throw std::invalid_argument("smth");
        sum += vec[i];
    }
    return sum;
}
