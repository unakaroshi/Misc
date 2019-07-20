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

  QString getFullname(const QString& abbr) const {
    // This prevents us from generating a default
    // constructor con CConstellationElement which
    // would be called every time this function
    // gets called.
    static CConstellationElement tmp("", "");
    auto el = m_data.value(abbr,tmp);
    return QString::fromStdString(el.getName());
  }

  QString getFullname(const std::string& abbr) const {    
    return getFullname(QString::fromStdString(abbr));    
  }

  
};
