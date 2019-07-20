#pragma once

#include <QString>

class CStarData
{
private:
  QString m_name{};
  bool m_hasRa { false };
  bool m_hasDecl { false };
  bool m_hasMv { false };

  double m_ra{0.0};
  double m_decl{0.0};
  double m_mv{0.0};
  QString m_constellation{};
  QString m_altname{};
  QString m_comment{};
  QString m_catalogname{};

public:
  CStarData() = default;
  CStarData(QString name, bool hasRa, double ra,
    bool hasDecl, double decl, bool hasMv, double mv,
    QString constellation, QString altname,
    QString comment, QString catalogname)
    : m_name(std::move(name))
    , m_hasRa(hasRa)
    , m_ra(ra)
    , m_hasDecl(hasDecl)
    , m_decl(decl)
    , m_hasMv(hasMv)
    , m_mv(mv)
    , m_constellation(std::move(constellation))
    , m_altname(std::move(altname))
    , m_comment(std::move(comment))
    , m_catalogname(std::move(catalogname))
  {

  }

  ~CStarData() = default;

  CStarData(const CStarData&) = default;
  CStarData& operator=(const CStarData&) & = default;
  CStarData(CStarData&&) = default;


  [[nodiscard]] QString getName() const noexcept { return m_name; }
  [[nodiscard]] QString getAltName() const noexcept { return m_altname; }
  [[nodiscard]] QString getConstellation() const noexcept { return m_constellation; }
  [[nodiscard]] QString getComment() const noexcept { return m_comment; }
  [[nodiscard]] QString getCatalogName() const noexcept { return m_catalogname; }
  [[nodiscard]] constexpr double getRa() const noexcept { return m_ra; }
  [[nodiscard]] constexpr double getDecl() const noexcept { return m_decl; }
  [[nodiscard]] constexpr double getMv () const noexcept { return m_mv; }

  [[nodiscard]] constexpr bool hasRa() const noexcept { return m_hasRa; }
  [[nodiscard]] constexpr bool hasDecl() const noexcept { return m_hasDecl; }
  [[nodiscard]] constexpr bool hasMv() const noexcept { return m_hasMv; }
  
};

inline bool operator< (const CStarData& lhs, const CStarData& rhs) {
  return lhs.getName() < rhs.getName();
}

