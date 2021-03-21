#include <vector>


struct Size_8{
    int x_ = 0;
    int y_ = 0;

    inline int sum() const {
        return x_ + y_;
    }
};


struct Size_12{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;

    inline int sum() const {
        return x_ + y_ + z_;
    }
};



struct Size_16{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int t_ = 0;

    inline int sum() const {
        return x_ + y_ + z_ + t_;
    }
};


struct Size_20{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int t_ = 0;
    int d_ = 0;

    inline int sum() const {
        return x_ + y_ + z_ + t_ + d_;
    }
};

struct Size_32{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int t_ = 0;
    int d_ = 0;
    int d1_ = 0;
    int d2_ = 0;
    int d3_ = 0;

    inline int sum() const {
        return x_ + y_ + z_ + t_ + d_+d1_+d2_+d3_;
    }
};


struct Size_64{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int t_ = 0;
    int d_ = 0;
    int d1_ = 0;
    int d2_ = 0;
    int d3_ = 0;

    Size_32 s_;

    inline int sum() const {
        return x_ + y_ + z_ + t_ + d_+d1_+d2_+d3_;
    }
};

struct Size_128{
    int x_ = 0;
    int y_ = 0;
    int z_ = 0;
    int t_ = 0;
    int d_ = 0;
    int d1_ = 0;
    int d2_ = 0;
    int d3_ = 0;

    Size_32 s_;
    Size_64 s1_;

    inline int sum() const {
        return x_ + y_ + z_ + t_ + d_+d1_+d2_+d3_;
    }
};





int f_8(std::vector<Size_8> vec){ 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_12(std::vector<Size_12> vec){ 	//NOT
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_16(std::vector<Size_16> vec){ 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_20(std::vector<Size_20> vec){ 	//NOT
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_32(std::vector<Size_32> vec){ 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_64(std::vector<Size_64> vec){ 	//vector
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}

int f_128(std::vector<Size_128> vec){ 	//NOT
    int sum = 0;
    for(size_t i=0; i<vec.size(); i++){
        sum += vec[i].sum();
    }
    return sum;
}
