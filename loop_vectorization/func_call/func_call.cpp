#include <vector>

int func_out(int lhs, int rhs) noexcept;

inline int func_inl(int lhs, int rhs){
    return lhs + rhs;
}



int call_inl(std::vector<int> vec){
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += func_inl(vec[i], vec[i]);
    }
    return sum;
}


int call_out(std::vector<int> vec, size_t size){
    int sum = 0;
    for(size_t i=0; i<size; i++){
        sum += func_out(vec[i], vec[i]);
    }
    return sum;
}
