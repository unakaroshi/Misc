#pragma once

#include <QObject>
#include <QMap>
#include <string>
#include "ConstellationElement.h"

class QIODevice;

class CConstellationData : public QObject
{
  Q_OBJECT

private:

  QMap<QString, CConstellationElement> m_data;

  bool read(QIODevice* device);

public:
  CConstellationData(QObject *parent = nullptr);
  ~CConstellationData();

  bool loadFromFile(const QString& filename);

  QString getFullname(const QString& abbr) const {
    auto el = m_data.value(abbr);
    return QString::fromStdString(el.getName());
  }

  QString getFullname(const std::string& abbr) const {    
    return getFullname(QString::fromStdString(abbr));    
  }
  
};
