#pragma once


#include <string>

class CConstellationElement {
private:
  std::string m_abbr {};
  std::string m_name {};

public:

  CConstellationElement(std::string abbr, std::string name) 
    : m_abbr(abbr)
    , m_name(name)
  { }

  [[nodiscard]] const std::string getAbbr() noexcept {
    return m_abbr;
  }

  [[nodiscard]] const std::string getName() noexcept {
    return m_name;
  }
};