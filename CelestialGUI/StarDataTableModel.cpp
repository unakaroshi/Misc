#include "StarDataTableModel.h"
#include "StarCatalog.h"
#include "ConstellationData.h"
#include <QDebug>
#include <QThread>
#include <QDir>
#include <QVector>
#include <qtconcurrentrun.h>

CStarDataTableModel::CStarDataTableModel(QObject *parent)
  : QAbstractTableModel(parent)
  , m_constellationData(new CConstellationData(this))
{

}

void CStarDataTableModel::loadData() {
  QVector<QFuture<bool>> results;


  auto start = std::chrono::steady_clock::now();


  QDir dirStarData("C:/Users/micha/Documents/Development/MyProjects/Misc/CelestialCalculations/StarData/");  
  QDir dirOtherData("C:/Users/micha/Documents/Development/MyProjects/Misc/CelestialCalculations/Data/");

  for (const QString& filename : dirStarData.entryList({ "*.dat" })) {
    CStarCatalog* catalog = new CStarCatalog(this);    
    QFuture<bool> res = QtConcurrent::run(catalog, &CStarCatalog::loadFromFile, dirStarData.absoluteFilePath(filename));
    results.push_back(res);
    m_catalogs.push_back(catalog);
  }

  QFuture<bool> constDataLoaded = QtConcurrent::run(m_constellationData, &CConstellationData::loadFromFile, dirOtherData.absoluteFilePath("ConstellationData.dat"));;
  results.push_back(constDataLoaded);

  int oldcount = 0;
  for (auto result : results) {
    result.waitForFinished();
  }
  

  beginInsertRows(QModelIndex(), 0, getAllStarsCount() - 1);
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
int CStarDataTableModel::getAllStarsCount() const {
  int rows = 0;
  std::for_each(m_catalogs.begin(), m_catalogs.end(), [&rows](auto elem) { rows += elem->size(); });
  return rows;
}

[[nodiscard]]
int CStarDataTableModel::getCatalogNumber(int row) const {
  int size = 0;
  int number = 0;

  for (auto* catalog : m_catalogs) {
    size += catalog->size();
    if (size > row) {
      return number;
    }
    ++number;
  }  
}

[[nodiscard]]
int CStarDataTableModel::getCatalogNumber(const QModelIndex& index) const {
  if (index.isValid()) {
    return getCatalogNumber(index.row());
  }
  return -1;
}

auto CStarDataTableModel::getElementIndex(int row) const {
  auto number = getCatalogNumber(row);  

  if (number < 0) {
    return std::make_pair(-1, -1);
  }

  if (m_catalogs.at(number)->isEmpty()) {
    return std::make_pair(-1, -1);
  }

  int numelements = 0;
  std::for_each(m_catalogs.begin(), m_catalogs.begin() + number, [&numelements](auto element) { 
    numelements += element->size(); 
    });

  auto element = row - numelements;
  //qDebug() << m_catalogs.at(number)->size();
  Q_ASSERT(element< m_catalogs.at(number)->size() );
  return std::make_pair(number,element);
}

auto CStarDataTableModel::getElementIndex(const QModelIndex& index) const {
  if (index.isValid()) {
    return getElementIndex(index.row());
    
  }
  return std::make_pair(-1, -1);
}

[[nodiscard]]
int CStarDataTableModel::rowCount(const QModelIndex& parent) const {
  if (parent.isValid()) {
    return 0;
  }
  return getAllStarsCount();
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
  if (!index.isValid()) {
    return QVariant();
  }

  if ( role == Qt::DisplayRole) {
    auto indizes = getElementIndex(index);

    auto catalogIndex = indizes.first;
    auto elementIndex = indizes.second;
    if (catalogIndex == -1 || elementIndex == -1) {
      return QVariant();
    }

    switch(index.column()) {
      case 0: 
        return QString::fromStdString(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getName());
      case 1: 
        return QString::number(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getRa());
      case 2: 
        return QString::number(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getDecl());
      case 3: 
        return QString::number(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getMv());
      case 4:
      {
        auto abbr = m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getConstellation();
        return m_constellationData->getFullname(abbr);
      }
      case 5: 
        return QString::fromStdString(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getAltName());
      case 6: 
        return QString::fromStdString(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getComment());
      case 7: 
        return QString::fromStdString(m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getCatalogName());
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

QStringList CStarDataTableModel::getStarCatalogNames() {
  QStringList ret;
  std::for_each(m_catalogs.begin(), m_catalogs.end(), [&](const CStarCatalog *cat) { 
    ret.append(cat->getCatalogName()); });
  return ret;
}
