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

  QMap<std::string, CConstellationElement> m_data;

  bool read(QIODevice* device);

public:
  CConstellationData(QObject *parent = nullptr);
  ~CConstellationData();

  bool loadFromFile(const QString& filename);
  
};
