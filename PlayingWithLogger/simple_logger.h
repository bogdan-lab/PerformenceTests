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
  void LogLine(const std::string& line) { fout_ << line << '\n'; }
  std::ofstream& AccessFout() { return fout_; }
};

#endif  // SIMPLE_LOGGER_H
