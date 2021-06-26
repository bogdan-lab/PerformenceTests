#ifndef LOG_WIDGET_H
#define LOG_WIDGET_H

#include <QPlainTextEdit>
#include <QTimer>
#include <chrono>
#include <mutex>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class LogWidget : public QPlainTextEdit {
  Q_OBJECT
 public:
  LogWidget(QWidget* parent = nullptr) : QPlainTextEdit(parent) {
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->setSingleShot(true);

    connect(
        timer, &QTimer::timeout, this,
        [this]() {
          PrintAll();
          this->QPlainTextEdit::repaint();
          timer->start();
        },
        Qt::QueuedConnection);
    timer->start();
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setWordWrapMode(QTextOption::NoWrap);
    this->setCenterOnScroll(false);
  }

  void AddText(std::string str) {
    std::lock_guard<std::mutex> lock(log_mutex_);
    coll_.push_back(std::move(str));
  }

  LogWidget& operator<<(std::string str) {
    coll_.push_back(std::move(str));
    return *this;
  }

  LogWidget& operator<<(const char* str) {
    coll_.emplace_back(str);
    return *this;
  }

  LogWidget& operator<<(char ch) {
    coll_.emplace_back(1, ch);
    return *this;
  }

  template <typename T>
  LogWidget& operator<<(const T& el) {
    coll_.push_back(std::to_string(el));
    return *this;
  }

 private:
  void PrintAll() {
    std::vector<std::string> buff;
    {
      std::lock_guard<std::mutex> lock(log_mutex_);
      buff.swap(coll_);
    }
    for (const auto& str : buff) {
      QPlainTextEdit::insertPlainText(QString::fromStdString(str));
    }
  }

  std::vector<std::string> coll_;
  QTimer* timer = nullptr;
  bool new_string_ = true;
  std::mutex log_mutex_;
};

#endif  // LOG_WIDGET_H
