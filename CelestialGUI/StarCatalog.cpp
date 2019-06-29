#include "StarCatalog.h"

#include <QDebug>
#include <QFile>
#include <QDir>
#include <qtconcurrentrun.h>
#include <QMessageBox>
#include <QDomDocument>





CStarCatalog::CStarCatalog(QObject *parent)
    : QObject(parent)
{

}

bool CStarCatalog::loadFromFile(const QString& filename) 
{
  QFile file(filename);

  if (!file.exists()) {
    return false;
  }

  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(nullptr, tr("StarCatalog"),
      tr("Cannot read file %1:\n%2.")
      .arg(QDir::toNativeSeparators(filename),
        file.errorString()));
    return false;
  }

  return read(&file);
}

bool CStarCatalog::read(QIODevice* device)
{
  
  QString errorStr;
  int errorLine;
  int errorColumn;
  QDomDocument domDocument;

  if (!domDocument.setContent(device, true, &errorStr, &errorLine, &errorColumn)) {
    QMessageBox::information(nullptr, tr("CStarCatalog"),
      tr("Parse error at line %1, column %2:\n%3")
      .arg(errorLine)
      .arg(errorColumn)
      .arg(errorStr));
    return false;
  }

  QDomElement root = domDocument.documentElement();

  if (root.tagName() != QStringLiteral("Catalog")) {
    QMessageBox::information(nullptr, tr("CStarCatalog"), tr("Seems to be no catalog"));
    return false;
  }

  qDebug() << "Loading StarCatalog";

  QDomElement element = root.firstChildElement(QStringLiteral("CatalogType"));
  qDebug() << "  CatalogType: " << element.text().trimmed();
  setCatalogName(element.text().trimmed());

  element = root.firstChildElement(QStringLiteral("Comments"));
  qDebug() << "  Comments: " << element.text().trimmed();
  setComment(element.text().trimmed());

  element = root.firstChildElement(QStringLiteral("Author"));
  qDebug() << "  Author: " << element.text().trimmed();
  setAuthor(element.text().trimmed());

  element = root.firstChildElement(QStringLiteral("Description"));
  qDebug() << "  Description: " << element.text().trimmed();
  setDescription(element.text().trimmed());

  element = root.firstChildElement(QStringLiteral("Source"));
  qDebug() << "  Source: " << element.text().trimmed();
  setSource(element.text().trimmed());


  element = root.firstChildElement(QStringLiteral("Data"));

  auto lines = element.text().trimmed().split("\r\n");
     

  auto current = lines.begin();
  QVector<QFuture<void>> results;

  while ((lines.end() - current) > 0) {
    int number = 5000;
    if (lines.end() - current < number) {
      number = lines.end() - current;
    }

    auto res = QtConcurrent::run(this, &CStarCatalog::extractLines, current, current + number);
    results.push_back(res);
    current = current + number;
  }

  for (auto res : results) {
    res.waitForFinished();
  }

   
  return false;
}

void CStarCatalog::extractLines(QList<QString>::iterator& begin, QList<QString>::iterator& end) {
  QList<CStarData> localStars;
  localStars.reserve(end-begin);

  std::string catname = m_catalogName.toStdString();

  std::for_each(begin, end, [&](const QString& line) {
    auto stringlist = line.split(",");
    auto name = stringlist[0].trimmed().toStdString();
    auto ra = stringlist[1].toDouble();
    auto decl = stringlist[2].toDouble();
    auto mv = stringlist[3].toDouble();
    auto constellation = stringlist[4].trimmed().toStdString();
    auto altname = stringlist[5].trimmed().toStdString();
    auto comment = stringlist[6].trimmed().toStdString();

    localStars.push_back(CStarData(name, ra, decl, mv, constellation, altname, comment, catname));
  });

  {
    QMutexLocker locker(&m_mutex);
    m_stars.append(localStars);
  }
  
  
}
