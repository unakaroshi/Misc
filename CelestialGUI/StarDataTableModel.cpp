#include "StarDataTableModel.h"
#include "StarCatalog.h"
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QVector>
#include <qtconcurrentrun.h>

CStarDataTableModel::CStarDataTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
  m_catalog = new CStarCatalog(this); 
}

void CStarDataTableModel::loadCatalogs() {
  QVector<QFuture<bool>> results;

  

  auto start = std::chrono::steady_clock::now();

  QDir dir("C:/Users/micha/Documents/Development/MyProjects/Misc/CelestialCalculations/StarData/");

  

  for (const QString& filename : dir.entryList({ "*.dat" })) {
    QFuture<bool> res = QtConcurrent::run(m_catalog, &CStarCatalog::loadFromFile, dir.absoluteFilePath(filename));
    results.push_back(res);
  }

  int oldcount = 0;
  for (auto result : results) {
    result.waitForFinished();
  }

  beginInsertRows(QModelIndex(), 0, m_catalog->getStarsCount() - 1);
  endInsertRows();

  auto end = std::chrono::steady_clock::now();
  qDebug() << "Elapsed time for SLOT (MAP) in milliseconds : "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << " ms\n";

  emit dataLoaded();
}

CStarDataTableModel::~CStarDataTableModel()
{
}

[[nodiscard]]
int CStarDataTableModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return m_catalog->getStarsCount();
}

[[nodiscard]]
int CStarDataTableModel::columnCount(const QModelIndex& parent) const {  
  if (parent.isValid()) {
    return 0;
  }
  return 8;
}

[[nodiscard]]
QVariant CStarDataTableModel::data(const QModelIndex& index, int role) const {
  if ( role == Qt::DisplayRole) {
    switch(index.column()) {
      case 0: return QString::fromStdString(m_catalog->getStars().at(index.row()).getName());
      case 1: return QString::number(m_catalog->getStars().at(index.row()).getRa());
      case 2: return QString::number(m_catalog->getStars().at(index.row()).getDecl());
      case 3: return QString::number(m_catalog->getStars().at(index.row()).getMv());
      case 4: return QString::fromStdString(m_catalog->getStars().at(index.row()).getConstellation());
      case 5: return QString::fromStdString(m_catalog->getStars().at(index.row()).getAltName());
      case 6: return QString::fromStdString(m_catalog->getStars().at(index.row()).getComment());
      case 7: return QString::fromStdString(m_catalog->getStars().at(index.row()).getCatalogName());
      default: return QVariant();
    
    }      
    
  }
  return QVariant();

}

QVariant CStarDataTableModel::headerData(int section, Qt::Orientation orientation, int role) const {


  switch (role) {
    default: break;
    case Qt::DisplayRole: {
      if ( orientation == Qt::Horizontal ) {
        switch(section) {
          case 0 : return "Name";
          case 1 : return "RA";
          case 2 : return "DECL";
          case 3 : return "MV";
          case 4 : return "Constellation";
          case 5 : return "Alternate name";
          case 6 : return "Comment";
          case 7 : return "CatalogName";
          default: return section;        
        }
      } else {
        return section;
      }
      
    }
    break;
  }

  return QVariant();
}
