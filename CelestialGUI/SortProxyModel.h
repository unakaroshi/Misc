#pragma once

#include <QAbstractProxyModel>

class CSortProxyModel : public QAbstractProxyModel 
{
  Q_OBJECT
public:
  CSortProxyModel(QObject* parent = nullptr) 
  : QAbstractProxyModel(parent) 
  {
  }

  void setSourceModel(QAbstractItemModel* newSourceModel) {
    beginResetModel();

    if (sourceModel()) {
      disconnect(sourceModel(), SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(rowsRemoved(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(rowsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      disconnect(sourceModel(), SIGNAL(rowsMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(rowsMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      disconnect(sourceModel(), SIGNAL(columnsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(columnsAboutToBeInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(columnsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(columnsInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(columnsAboutToBeRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(columnsAboutToBeRemoved(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(columnsRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(columnsRemoved(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(columnsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(columnsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      disconnect(sourceModel(), SIGNAL(columnsMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(columnsMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      disconnect(sourceModel(), SIGNAL(modelAboutToBeReset()),
        this, SIGNAL(modelAboutToBeReset()));
      disconnect(sourceModel(), SIGNAL(modelReset()),
        this, SIGNAL(modelReset()));
      disconnect(sourceModel(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
        this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)));
      disconnect(sourceModel(), SIGNAL(headerDataChanged(Qt::Orientation, int, int)),
        this, SIGNAL(headerDataChanged(Qt::Orientation, int, int)));
      disconnect(sourceModel(), SIGNAL(layoutAboutToBeChanged()),
        this, SIGNAL(layoutAboutToBeChanged()));
      disconnect(sourceModel(), SIGNAL(layoutChanged()),
        this, SIGNAL(layoutChanged()));
    }

    QAbstractProxyModel::setSourceModel(newSourceModel);

    if (sourceModel()) {
      connect(sourceModel(), SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(rowsRemoved(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(rowsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      connect(sourceModel(), SIGNAL(rowsMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(rowsMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      connect(sourceModel(), SIGNAL(columnsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(columnsAboutToBeInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(columnsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(columnsInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(columnsAboutToBeRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(columnsAboutToBeRemoved(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(columnsRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(columnsRemoved(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(columnsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(columnsAboutToBeMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      connect(sourceModel(), SIGNAL(columnsMoved(const QModelIndex&, int, int, const QModelIndex&, int)),
        this, SIGNAL(columnsMoved(const QModelIndex&, int, int, const QModelIndex&, int)));
      connect(sourceModel(), SIGNAL(modelAboutToBeReset()),
        this, SIGNAL(modelAboutToBeReset()));
      connect(sourceModel(), SIGNAL(modelReset()),
        this, SIGNAL(modelReset()));
      connect(sourceModel(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
        this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)));
      connect(sourceModel(), SIGNAL(headerDataChanged(Qt::Orientation, int, int)),
        this, SIGNAL(headerDataChanged(Qt::Orientation, int, int)));
      connect(sourceModel(), SIGNAL(layoutAboutToBeChanged()),
        this, SIGNAL(layoutAboutToBeChanged()));
      connect(sourceModel(), SIGNAL(layoutChanged()),
        this, SIGNAL(layoutChanged()));
    }
    endResetModel();
  }

  /* QAbstractProxyModel methods */
  QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override{
    if (!sourceModel()) {
      return QModelIndex();
    }
    return sourceModel()->index(row, column, parent);
  }

  QModelIndex parent(const QModelIndex& child) const override {    
    // No tree,
    return QModelIndex();
  }
  
  int rowCount(const QModelIndex& parent = QModelIndex()) const override {
    if (!sourceModel()) {
      return 0;
    }
    return sourceModel()->rowCount(parent);
  }

  int columnCount(const QModelIndex& parent) const override {
    if (!sourceModel()) {
      return 0;
    }
    return sourceModel()->columnCount(parent);
  }

  QModelIndex mapToSource(const QModelIndex& index) const override {
    if (!sourceModel()) {
      return QModelIndex();
    }
    return sourceModel()->index(index.row(), index.column());

  }

  QModelIndex mapFromSource(const QModelIndex& index) const override {
    if (!index.isValid() || !sourceModel()) {
      return QModelIndex();
    }
      
    
    return sourceModel()->index(index.row(), index.column());
  }
};