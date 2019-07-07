#pragma once


#include <iostream>
#include <chrono>
#include <QDebug>


class ScopedTimer {

  using ClockType = std::chrono::steady_clock;
private:
  const char* m_function {};
  const ClockType::time_point m_start  {};

public:
  

  ScopedTimer(const char* func) 
    : m_function { func }
    , m_start { ClockType::now() } 
  {
  }

  ScopedTimer(const ScopedTimer&) = delete;
  ScopedTimer(ScopedTimer&&) = delete;
  auto operator=(const ScopedTimer&)->ScopedTimer & = delete;
  auto operator=(ScopedTimer&&)->ScopedTimer & = delete;

  ~ScopedTimer() {    
    auto stop = ClockType::now();
    auto duration = (stop - m_start); 
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    qDebug() << ms << " ms " << m_function;
  }


};
