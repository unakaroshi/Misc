#pragma once

#include <string>

class CStarData
{
private:
  std::string m_name{};
  double m_ra{0.0};
  double m_decl{0.0};
  double m_mv{0.0};
  std::string m_constellation{};
  std::string m_altname{};
  std::string m_comment{};
  std::string m_catalogname{};

public:
  CStarData() {  }
  CStarData(const std::string& name, double ra, double decl, double mv,
    const std::string& constellation, const std::string& altname,
    const std::string& comment, const std::string& catalogname)
    : m_name(name)
    , m_ra(ra)
    , m_decl(decl)
    , m_mv(mv)
    , m_constellation(constellation)
    , m_altname(altname)
    , m_comment(comment)
    , m_catalogname(catalogname)
  {

  }

  ~CStarData() = default;

  CStarData(const CStarData&) = default;
  CStarData& operator=(const CStarData&) & = default;
  CStarData(CStarData&&) = default;


  [[nodiscard]] std::string getName() const noexcept { return m_name; }
  [[nodiscard]] std::string getAltName() const noexcept { return m_altname; }
  [[nodiscard]] std::string getConstellation() const noexcept { return m_constellation; }
  [[nodiscard]] std::string getComment() const noexcept { return m_comment; }
  [[nodiscard]] std::string getCatalogName() const noexcept { return m_catalogname; }
  [[nodiscard]] constexpr double getRa() const noexcept { return m_ra; }
  [[nodiscard]] constexpr double getDecl() const noexcept { return m_decl; }
  [[nodiscard]] constexpr double getMv () const noexcept { return m_mv; }

};
