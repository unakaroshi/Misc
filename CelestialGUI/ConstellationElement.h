#pragma once


#include <string> // NOLINT

class CConstellationElement {
private:
  std::string m_abbr {};
  std::string m_name {};

public:

  CConstellationElement(std::string abbr, std::string name) 
    : m_abbr(std::move(abbr))
    , m_name(std::move(name))
  { }

  [[nodiscard]] std::string getAbbr() const noexcept {
    return m_abbr;
  }

  [[nodiscard]] std::string getName() const noexcept {
    return m_name;
  }
};