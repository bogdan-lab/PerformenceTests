#include <vector>
#include <algorithm>




int bad_idx(std::vector<int> vec, std::vector<size_t> n){ 	//NOT
    int sum = 0;
    for(size_t i=0; i<n.size(); i++){
        sum += vec[n[i]];
    }
    return sum;
}


int stride_sum(std::vector<int> vec, size_t stride){ 	 	//vector (probably can be changed at runtime...)
    int sum = 0;
    if (stride>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-stride; i+=stride){
        sum += vec[i];
    }
    return sum;
}



int stride_sum_2(std::vector<int> vec){ 	//vector
    int sum = 0;
    if (2>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-2; i+=2){
        sum += vec[i];
    }
    return sum;
}


int stride_sum_4(std::vector<int> vec){ 	//vector
    int sum = 0;
    if (4>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-4; i+=4){
        sum += vec[i];
    }
    return sum;
}


int stride_sum_8(std::vector<int> vec){        //NOT
    int sum = 0;
    if (8>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-8; i+=8){
        sum += vec[i];
    }
    return sum;
}



int stride_sum_10(std::vector<int> vec){        //NOT
    int sum = 0;
    if (10>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-10; i+=10){
        sum += vec[i];
    }
    return sum;
}


int stride_sum_16(std::vector<int> vec){        //NOT
    int sum = 0;
    if (16>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-16; i+=16){
        sum += vec[i];
    }
    return sum;
}



double stride_sum_4(std::vector<double> vec){        //NOT
    double sum = 0;
    if (4>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-4; i+=4){
        sum += vec[i];
    }
    return sum;
}


double stride_sum_2(std::vector<double> vec){        //NOT
    double sum = 0;
    if (2>vec.size()) return sum;
    for(size_t i=0; i<vec.size()-2; i+=2){
        sum += vec[i];
    }
    return sum;
}

