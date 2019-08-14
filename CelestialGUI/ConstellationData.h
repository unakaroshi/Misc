#pragma once

#include <QObject> // NOLINT
#include <QMap> // NOLINT
#include <string> // NOLINT
#include "ConstellationElement.h"

class QIODevice;

class CConstellationData : public QObject
{
  Q_OBJECT // NOLINT

private:

  QMap<QString, CConstellationElement> m_data;

  bool read(QIODevice* device);

public:

  CConstellationData(QObject *parent = nullptr);
  ~CConstellationData() = default;

  CConstellationData(const CConstellationData&) = delete;
  CConstellationData(CConstellationData&&) = delete; 
  CConstellationData& operator=(const CConstellationData&)= delete;
  CConstellationData& operator=(CConstellationData&&) = delete;

  bool loadFromFile(const QString& filename);

  [[nodiscard]] QString getFullname(const QString& abbr) const noexcept {
    // This prevents us from generating a default
    // constructor con CConstellationElement which
    // would be called every time this function
    // gets called.
    static CConstellationElement tmp("", "",0.0,0.0,"",0.0,0.0,"");
    return m_data.value(abbr,tmp).getName();    
  }

  [[nodiscard]] CConstellationElement getData(const QString& abbr) const noexcept {
    // This prevents us from generating a default
    // constructor con CConstellationElement which
    // would be called every time this function
    // gets called.
    static CConstellationElement tmp("", "", 0.0, 0.0, "", 0.0, 0.0, "");
    return m_data.value(abbr, tmp);
  }
 
};
