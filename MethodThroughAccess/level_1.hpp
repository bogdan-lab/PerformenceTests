#ifndef LEVEL_1_HPP
#define LEVEL_1_HPP


#include <memory>
#include "level_2.hpp"

typedef std::shared_ptr<Info> InfoPtr;

class Config {
private:
    InfoPtr info_;
public:

    Config();

    const InfoPtr& GetInfo() const ;

};



class ConfigInl {
private:
    InfoPtr info_;
public:
    ConfigInl(): info_(std::make_shared<Info>()) {}
    const InfoPtr& GetInfo() const {return info_;}

};




#endif //LEVEL_1_HPP


