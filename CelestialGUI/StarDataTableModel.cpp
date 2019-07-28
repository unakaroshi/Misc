#include "StarDataTableModel.h"
#include "StarCatalog.h"
#include "ConstellationData.h"
#include <QDebug> // NOLINT
#include <QThread> // NOLINT
#include <QDir> // NOLINT
#include <QVector> // NOLINT
#include <qtconcurrentrun.h> // NOLINT
#include "ScopedTimer.hpp"

CStarDataTableModel::CStarDataTableModel(QObject *parent)
  : QAbstractTableModel(parent)
  , m_constellationData(new CConstellationData(this))
{

}

void CStarDataTableModel::loadData() {
  ScopedTimer t(__func__);
  QVector<QFuture<bool>> results;


  QDir dirStarData("C:/Users/micha/Documents/Development/MyProjects/Misc/CelestialCalculations/StarData/");  
  QDir dirOtherData("C:/Users/micha/Documents/Development/MyProjects/Misc/CelestialCalculations/Data/");

  for (const QString& filename : dirStarData.entryList({ "*.dat" })) {
    auto* catalog = new CStarCatalog();    
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
    
  emit dataLoaded();
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
  return -1;
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

  if (m_catalogs.at(number)->empty()) {
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
  
  return COLUMN_COUNT;
}

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
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
      case to_underlying(Column::NAME):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getName();
      case to_underlying(Column::RA):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getRa();
      case to_underlying(Column::DECL):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getDeclString();
      case to_underlying(Column::MV):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getMvString();
      case to_underlying(Column::CONSTELLATION):
      {
        auto abbr = m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getConstellation();
        return m_constellationData->getFullname(abbr);
      }
      case to_underlying(Column::ALT_NAME):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getAltName();
      case to_underlying(Column::COMMENT):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getComment();
      case to_underlying(Column::CATALOG):
        return m_catalogs.at(catalogIndex)->getStars().at(elementIndex).getCatalogName();
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
          case to_underlying(Column::NAME) : return "Name";
          case to_underlying(Column::RA) : return "RA";
          case to_underlying(Column::DECL) : return "DECL";
          case to_underlying(Column::MV) : return "MV";
          case to_underlying(Column::CONSTELLATION) : return "Constellation";
          case to_underlying(Column::ALT_NAME) : return "Alternate name";
          case to_underlying(Column::COMMENT) : return "Comment";
          case to_underlying(Column::CATALOG) : return "CatalogName";
          default: return QVariant();        
        }
      } else {
        return QVariant();
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
