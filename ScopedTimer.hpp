#pragma once


#include <iostream> // NOLINT
#include <chrono> // NOLINT
#include <QDebug> // NOLINT


class ScopedTimer {
  using ClockType = std::chrono::steady_clock;

private:
  const char* m_function {};
  const ClockType::time_point m_start  {};

public:
  explicit ScopedTimer(const char* func) 
    : m_function { func }
    , m_start { ClockType::now() } 
  {
  }

  ScopedTimer(const ScopedTimer&) = delete;
  ScopedTimer(ScopedTimer&&) = delete;

  ScopedTimer& operator=(const ScopedTimer&) = delete;
  ScopedTimer& operator=(ScopedTimer&&) = delete;

  ~ScopedTimer() {    
    auto stop = ClockType::now();
    auto duration = (stop - m_start); 
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    qDebug() << ms << " ms " << m_function;
  }


};
