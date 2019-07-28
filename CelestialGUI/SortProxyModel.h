#pragma once

#include <QAbstractProxyModel> // NOLINT
//#include <QMap>
#include <QVector> // NOLINT
#include <QPair> // NOLINT
#include <QDebug> // NOLINT
#include <vector> // NOLINT
#include <utility> // NOLINT
#include <algorithm> // NOLINT
#include <execution> // NOLINT

#include "ScopedTimer.hpp"

class SortProxyModelLt {
public:
  bool operator()(const std::pair<QString, int>& r1, const std::pair<QString, int>& r2) const {
    return r1.first < r2.first;
  }
};

class SortProxyModelGt {
public:
  bool operator()(const std::pair<QString, int>& r1, const std::pair<QString, int>& r2) const {
    return r1.first > r2.first;
  }

};

class CSortProxyModel : public QAbstractProxyModel {
  Q_OBJECT

private:
  std::vector<std::pair<QString, int>> m_mapping;

public:
  CSortProxyModel(QObject* parent = nullptr)
    : QAbstractProxyModel(parent) {
  }

  void setSourceModel(QAbstractItemModel* newSourceModel) {
    beginResetModel();

    if (sourceModel()) {
      disconnect(sourceModel(), SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
      disconnect(sourceModel(), SIGNAL(rowsInserted(QModelIndex, int, int)), this,
        SLOT(onRowsInserted(QModelIndex, int, int)));

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
    m_mapping.clear();
    m_mapping.reserve(0);

    if (sourceModel()) {
      connect(sourceModel(), SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsInserted(const QModelIndex&, int, int)),
        this, SIGNAL(rowsInserted(const QModelIndex&, int, int)));
      connect(sourceModel(), SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)),
        this, SIGNAL(rowsAboutToBeRemoved(const QModelIndex&, int, int)));

      connect(sourceModel(), SIGNAL(rowsInserted(QModelIndex, int, int)), this,
        SLOT(onRowsInserted(QModelIndex, int, int)));

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



  Q_SLOT void onRowsInserted(const QModelIndex& parent, int first, int last) {
    Q_UNUSED(parent);

    m_mapping.reserve(static_cast<size_t>(last) - static_cast<size_t>(first) + 1 + m_mapping.size());

    size_t capacity = m_mapping.capacity();  // Needed for the Q_ASSERT later.

    {
      ScopedTimer t(__func__);

      for (int i = first; i <= last; ++i) {
        QModelIndex idx = createIndex(i, 0);
        m_mapping.emplace_back(data(idx, Qt::DisplayRole).toString(), i);
      }
    }
    Q_ASSERT(capacity == m_mapping.capacity());
    Q_ASSERT(m_mapping.capacity() == m_mapping.size());

    //  {

    //    std::sort(std::execution::par_unseq, m_mapping.begin(), m_mapping.end(), [](const auto &a, const auto &b) {
    //      return a.first < b.first;
    //    });
    //  }
  }


  QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override {
    Q_UNUSED(parent);

    if (!sourceModel() || row < 0 || column < 0 || parent.isValid()) {
      return QModelIndex();
    }

    return createIndex(row, column);
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
    if (!index.isValid() || !sourceModel()) {
      return QModelIndex();
    }


    if (index.row() >= m_mapping.size()) {
      return sourceModel()->index(index.row(), index.column());
    }

    auto elem = m_mapping.at(index.row());

    return createIndex(elem.second, index.column());
  }

  QModelIndex mapFromSource(const QModelIndex& index) const override {
    if (!index.isValid() || !sourceModel()) {
      return QModelIndex();
    }

    auto it = std::find_if(std::execution::par_unseq, m_mapping.begin(), m_mapping.end(), [&index](const auto& a) {
      return a.second == index.row();
      });

    if (it == m_mapping.end()) {
      return QModelIndex();
    }

    return createIndex(it - m_mapping.begin(), index.column());
  }

  void sort(int column, Qt::SortOrder order) override {
    ScopedTimer t(__func__);
    beginResetModel();
    if (order == Qt::AscendingOrder) {
      std::stable_sort(std::execution::par_unseq, m_mapping.begin(), m_mapping.end(), SortProxyModelLt {});
    } else {
      std::stable_sort(std::execution::par_unseq, m_mapping.begin(), m_mapping.end(), SortProxyModelGt {});
    }

    endResetModel();
  }
};
