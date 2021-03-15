#ifndef LEVEL_3_HPP
#define LEVEL_3_HPP

#include <string>


struct LhsColl{
    double start_ = 1.25;
    double end_ = 34.19;
    double smth_ = 73.20;
    size_t id_ = 0;
    std::string some_string_ = "This is some random but still quite long string written in English! Just want to avoid short string optimization.";
    int64_t x_ = 0;
    int64_t y_ = 35;
    int64_t z_ = 68;
    std::string another_string_ = "This is ANOTHER!!! random but still quite long string written in English! Just want to avoid short string optimization.";

    LhsColl() = default;
};


struct RhsColl{
    double start_ = 1.25;
    double end_ = 34.19;
    double smth_ = 73.20;
    size_t id_ = 0;
    std::string some_string_ = "This is some random but still quite long string written in English! Just want to avoid short string optimization.";
    int64_t x_ = 0;
    int64_t y_ = 35;
    int64_t z_ = 68;
    std::string another_string_ = "This is ANOTHER!!! random but still quite long string written in English! Just want to avoid short string optimization.";

    RhsColl() = default;
};


#endif 	//LEVEL_3_HPP
