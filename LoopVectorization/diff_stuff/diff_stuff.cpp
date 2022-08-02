#include <vector>




int while_test(std::vector<int> vec){ 	 	//vector
    int sum = 0;
    size_t idx=0;
    while(idx<vec.size()){
        sum += vec[idx];
        idx++;
    }
    return sum;
}


int while_test_2(std::vector<int> vec){ 	 	//NOT
    int sum = 0;
    size_t idx=0;
    while(vec[idx]<10){
        sum += vec[idx];
        idx++;
    }
    return sum;
}



int mod_test_bad(std::vector<int> vec, int mod){ 	 	//NOT
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i]%mod;
    }
    return sum;
}


int mod_test_good(std::vector<int> vec){  	 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i]%5;
    }
    return sum;
}




double conv_test_bad(std::vector<double> d, std::vector<float> f){ 	 	//NOT
    double sum = 0;
    for(size_t i=0; i<d.size(); i++){
        sum += d[i] + f[i];
    }
    return sum;
}


double conv_test_good(std::vector<double> d, std::vector<double> f){ 	//vector
    double sum = 0;
    for(size_t i=0; i<d.size(); i++){
        sum += d[i] + f[i];
    }
    return sum;
}


int bool_conv(std::vector<int> v, int num){ 	 	 	//vector
    int sum=0;
    for(size_t i=0; i<v.size(); i++){
        sum += v[i]>num;
    }
    return sum;
}


int bool_conv(std::vector<double> v, double num){ 	 	 	//NOT
    int sum=0;
    for(size_t i=0; i<v.size(); i++){
        sum += v[i]>num;
    }
    return sum;
}
