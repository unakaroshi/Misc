#include "CelestialGUI.h"
#include "StarCatalog.h"

#include <qtconcurrentrun.h>  // NOLINT
#include <QCheckBox>          // NOLINT
#include <QDebug>             // NOLINT
#include <QScrollBar>
#include <QTimer>  // NOLINT

CelestialGUI::CelestialGUI(QWidget* parent) : QDialog(parent) {
  ui.setupUi(this);

  ui.btn_load->setVisible(false);

  m_pProxyModel->setSourceModel(m_pModel);

  ui.tableView->setSortingEnabled(true);
  ui.tableView->setModel(m_pProxyModel);
  //ui.tableView->setModel(m_pModel);

  ui.tableView->setColumnHidden(1, true);
  ui.tableView->setColumnHidden(2, true);
  ui.tableView->setColumnHidden(3, true);
  ui.tableView->setColumnHidden(4, true);
  ui.tableView->setColumnHidden(7, true);

  connect(m_pProxyModel, &QAbstractItemModel::modelAboutToBeReset, [&]() {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    ui.tableView->setEnabled(false);
  });

  connect(m_pProxyModel, &QAbstractItemModel::modelReset, [&]() {
    QApplication::restoreOverrideCursor();
    ui.tableView->setEnabled(true);
  });

  connect(m_pModel, &CStarDataTableModel::dataLoaded, ui.tableView,
          &QTableView::resizeColumnsToContents);

  connect(m_pModel, &CStarDataTableModel::dataLoaded, [&]() {
    auto catalogs = m_pModel->getStarCatalogNames();
    std::for_each(catalogs.begin(), catalogs.end(),
                  [&](const QString& cat) { ui.cb_catalogs->addItem(cat); });
  });

  connect(ui.tableView->verticalScrollBar(), &QScrollBar::valueChanged,
          [&](int value) {
              qDebug() << "TopLeft: "
                       << m_pModel
                              ->data(ui.tableView->indexAt(
                                         ui.tableView->rect().topLeft()),
                                     Qt::DisplayRole)
                              .toString()
                       << "    BottomLeft: "
                       << m_pModel
                              ->data(ui.tableView->indexAt(
                                         ui.tableView->rect().bottomLeft()),
                                     Qt::DisplayRole)
                              .toString();      
          });

  
  connect(ui.cb_catalogs,
          qOverload<const QString&>(&QComboBox::currentTextChanged),
          [&](const QString& s) {
            qDebug() << s;

            // m_pProxyModel->setFilterKeyColumn(7);
            // m_pProxyModel->setFilterFixedString(s);
          });

  QTimer::singleShot(200, [&]() {
    QtConcurrent::run(m_pModel, &CStarDataTableModel::loadData);
  });
}
