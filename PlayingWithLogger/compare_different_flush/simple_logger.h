#ifndef SIMPLE_LOGGER_H
#define SIMPLE_LOGGER_H

#include <fstream>
#include <string>

class SimpleLogger {
 private:
  std::ofstream fout_;

 public:
  SimpleLogger() = delete;
  SimpleLogger(const std::string& fname) : fout_(fname) {}
  template <typename ValueType>
  SimpleLogger& operator<<(ValueType value) {
    fout_ << value;
    return *this;
  }
};

#endif  // SIMPLE_LOGGER_H
