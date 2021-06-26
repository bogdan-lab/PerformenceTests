#include <QApplication>

#include "log_widget.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  LogWidget logObj;
  logObj.AddText("Hello World!\n");
  logObj << "IntValues = " << 1 << " ; " << 2 << '\n';
  logObj << "DoubleValues = " << 3.14 << " ; " << 9.8 << '\n';
  logObj.show();
  return a.exec();
}
