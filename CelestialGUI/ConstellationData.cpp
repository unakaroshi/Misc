//#include <QFile>
#include "ConstellationData.h"
#include <QDebug>        // NOLINT
#include <QDir>          // NOLINT
#include <QDomDocument>  // NOLINT
#include <QMessageBox>   // NOLINT
#include <QThread>

bool CConstellationData::read(QIODevice* device) {
  QString errorStr;
  int errorLine;
  int errorColumn;
  QDomDocument domDocument;

  if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                              &errorColumn)) {
    QMessageBox::information(nullptr, tr("CConstellationData"),
                             tr("Parse error at line %1, column %2:\n%3")
                                 .arg(errorLine)
                                 .arg(errorColumn)
                                 .arg(errorStr));
    return false;
  }

  QDomElement root = domDocument.documentElement();

  if (root.tagName() != QStringLiteral("Constellations")) {
    QMessageBox::information(nullptr, tr("CConstellationData"),
                             tr("Seems to be no constellation data"));
    return false;
  }

  // qDebug() << "Loading Constellationsdata";

  // QDomElement element = root.firstChildElement(QStringLiteral("Revision"));
  // qDebug() << "  Revision " << element.text().trimmed();

  // element = root.firstChildElement(QStringLiteral("Date"));
  // qDebug() << "  Date " << element.text().trimmed();

  QDomElement basicData = root.firstChildElement(QStringLiteral("BasicData"));

  // QDomElement element =
  // basicData.firstChildElement(QStringLiteral("Description")); qDebug() << "
  // Desc: " << element.text().trimmed();

  auto element = basicData.firstChildElement(QStringLiteral("Data"));
  //qDebug() << "  Data: " << element.text().trimmed();

  auto lines = element.text().trimmed().split("\r\n");

  for (const QString& line : lines) {
    auto elements = line.split(',');
    // qDebug() << elements[1].trimmed();

    auto abbr = elements[0].trimmed();
    auto name = elements[1].trimmed();

    auto centerRA = elements[2].trimmed().toDouble();
    auto centerDecl = elements[3].trimmed().toDouble();
    auto brightestStar = elements[4].trimmed();
    auto starRA = elements[5].trimmed().toDouble();
    auto starDecl = elements[6].trimmed().toDouble();
    auto meaning = elements[7].trimmed();
    // qDebug() << "Inserting: " << abbr << QString::fromStdString(name);

    m_data.insert(
        abbr, CConstellationElement(abbr, name, centerRA, centerDecl,
                                    brightestStar, starRA, starDecl, meaning));
  }

  return true;
}

CConstellationData::CConstellationData(QObject* parent) : QObject(parent) {}

bool CConstellationData::loadFromFile(const QString& filename) {
  //qDebug() << __func__ << QThread::currentThreadId();
  QFile file(filename);

  if (!file.exists()) {
    return false;
  }

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(
        nullptr, tr("StarCatalog"),
        tr("Cannot read file %1:\n%2.")
            .arg(QDir::toNativeSeparators(filename), file.errorString()));
    return false;
  }

  return read(&file);
}
