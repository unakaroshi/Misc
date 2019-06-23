#pragma once

#include <QAbstractTableModel>

class CStarCatalog;

class CStarDataTableModel : public QAbstractTableModel
{
  Q_OBJECT
private:
  CStarCatalog* m_catalog;



  enum class Column {
    NAME = 0,
    RA = 1,
    DECL = 2,
    MV = 3,
    CONSTELLATION = 4,
    ALT_NAME = 5,
    COMMENT = 6
  };
public:


  CStarDataTableModel(QObject *parent);

  void loadCatalogs();
  
  ~CStarDataTableModel();

  [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

  [[nodiscard]] int columnCount(const QModelIndex& parent) const override;

  [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

signals:
  void dataLoaded();
};
