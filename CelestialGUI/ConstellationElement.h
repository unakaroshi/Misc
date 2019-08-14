#pragma once


#include <QString> // NOLINT

class CConstellationElement {
private:
  QString m_abbr {};
  QString m_name {};
  double m_ra { 0.0 };
  double m_decl { 0.0 };  
  QString m_brightestStar { }; 
  double m_starRa { 0.0 };
  double m_starDecl { 0.0 };
  QString m_meaning {};
public:

  CConstellationElement(QString abbr, QString name, double ra, double decl, QString brightestStar,
                        double starRA, double starDecl, QString meaning) 
    : m_abbr(std::move(abbr))
    , m_name(std::move(name))
    , m_ra(ra)
    , m_decl(decl)
    , m_brightestStar(std::move(brightestStar))
    , m_starRa(starRA)
    , m_starDecl(starDecl)
    , m_meaning(std::move(meaning))
  { }

  [[nodiscard]] QString getAbbr() const noexcept {
    return m_abbr;
  }

  [[nodiscard]] QString getName() const noexcept {
    return m_name;
  }

  [[nodiscard]] double getRa() const noexcept {
    return m_ra;
  }

  [[nodiscard]] double getDecl() const noexcept {
    return m_decl;
  }

  [[nodiscard]] QString getBrightestStar() const noexcept {
    return m_brightestStar;
  }

  [[nodiscard]] double getStarRa() const noexcept {
    return m_starRa;
  }

  [[nodiscard]] double getStarDecl() const noexcept {
    return m_starDecl;
  }

  [[nodiscard]] QString getMeaning() const noexcept {
    return m_meaning;
  }
};