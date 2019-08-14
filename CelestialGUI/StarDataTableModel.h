#pragma once

#include <QAbstractTableModel> // NOLINT

class CStarCatalog;
class CConstellationData;

class CStarDataTableModel : public QAbstractTableModel {
  Q_OBJECT // NOLINT
private:
  //CStarCatalog* m_catalog;

  QVector<CStarCatalog*> m_catalogs { };

  CConstellationData* m_constellationData { nullptr };

  [[nodiscard]] int getCatalogNumber(int row) const;

  [[nodiscard]] int getCatalogNumber(const QModelIndex& index) const;

  [[nodiscard]] auto getElementIndex(int row) const;

  [[nodiscard]] auto getElementIndex(const QModelIndex& index) const;
  
  [[nodiscard]] QVariant getToolTipRole(const QModelIndex& index) const;

  [[nodiscard]] QVariant getDisplayRole(const QModelIndex& index) const;


  enum class Column {
    NAME = 0,
    RA = 1,
    DECL = 2,
    MV = 3,
    CONSTELLATION = 4,
    ALT_NAME = 5,
    COMMENT = 6,
    CATALOG = 7
  };

  const int COLUMN_COUNT = 8;
public:
  CStarDataTableModel(QObject* parent = nullptr);
  ~CStarDataTableModel() override = default;

  CStarDataTableModel(const CStarDataTableModel&) = delete;
  CStarDataTableModel(CStarDataTableModel&&) = delete;
  CStarDataTableModel operator=(const CStarDataTableModel&&) = delete;


  void loadData();

  [[nodiscard]] int getAllStarsCount() const;

  [[nodiscard]] int rowCount(const QModelIndex& parent) const override;

  [[nodiscard]] int columnCount(const QModelIndex& parent) const override;

  [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;


  [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

  [[nodiscard]] QStringList getStarCatalogNames();

signals: // NOLINT
  void dataLoaded();
};
