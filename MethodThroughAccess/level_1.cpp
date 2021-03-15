#include "level_1.hpp"
#include <memory>


Config::Config() : info_(std::make_shared<Info>()) {}

const InfoPtr& Config::GetInfo() const{ return info_; }

