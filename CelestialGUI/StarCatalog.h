#pragma once

#include <QObject>
#include <QMutex>
#include "StarData.h"


class QIODevice;

class CStarCatalog : public QObject
{
  Q_OBJECT

private:
  
  QString m_catalogName{};
  QString m_comment{};
  QString m_author{};
  QString m_description{};
  QString m_source{};

  QList<CStarData> m_stars {};
  //std::list<CStarData> m_stars { };

  QMutex m_mutex {};

protected:
  bool read(QIODevice* device);

  void extractLines(QList<QString>::iterator &begin, QList<QString>::iterator &end);

public:
  CStarCatalog(QObject* parent = nullptr);
  virtual ~CStarCatalog() = default;

  CStarCatalog(const CStarCatalog& other) = default;
  CStarCatalog(CStarCatalog&& other) = default;
 
  [[nodiscard]] bool loadFromFile(const QString& filename);

  void setCatalogName(const QString& s) noexcept { m_catalogName = s; }
  [[nodiscard]] QString getCatalogName() const { return m_catalogName; }

  void setDescription(const QString& s) noexcept { m_description = s; }
  [[nodiscard]] QString getDescription() const { return m_description; }

  void setAuthor(const QString& s) noexcept { m_author = s; }
  [[nodiscard]] QString getAuthor() const { return m_author; }

  void setComment(const QString& s) noexcept { m_comment = s; }
  [[nodiscard]] QString getComment() const { return m_comment; }

  void setSource(const QString& s) noexcept { m_source = s; }
  [[nodiscard]] QString getSource() const noexcept { return m_source; }

  [[nodiscard]] int size() const noexcept { return m_stars.size();
  }

  [[nodiscard]] bool isEmpty() const noexcept { return m_stars.isEmpty(); }
  
  [[nodiscard]] int getStarsCount() const noexcept { return m_stars.size(); }

  [[nodiscard]] const auto& getStars() const noexcept { return m_stars; }
};
