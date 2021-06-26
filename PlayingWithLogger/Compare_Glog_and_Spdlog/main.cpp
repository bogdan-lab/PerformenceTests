#include <QApplication>

#include "log_widget.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

int RunLogger(int argc, char* argv[]) {
  QApplication a(argc, argv);
  LogWidget logObj;
  logObj.AddText("Hello World!\n");
  logObj << "IntValues = " << 1 << " ; " << 2 << '\n';
  logObj << "DoubleValues = " << 3.14 << " ; " << 9.8 << '\n';
  logObj.show();
  return a.exec();
}

auto logger = spdlog::basic_logger_mt("basic_logger", "logs/basic-log.txt");

void error_handle_example() {
  auto console = spdlog::stdout_color_mt("console");
  spdlog::set_error_handler([](const std::string& msg) {
    spdlog::get("basic_logger")->error("THIS IS ERROR MSG {}", msg);
  });
  console->info("some invalid message to trigger an error {}{}{}{}", 3);
  int x = 10;
  while (x--) {
    console->info("I continue work {}", x);
  }
}

int main(int argc, char* argv[]) {
  error_handle_example();

  return 0;
}
