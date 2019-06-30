#include "CelestialGUI.h"
#include "StarCatalog.h"
//#include "FilerProxyModel.h"

#include <QSortFilterProxyModel>
#include <QCheckBox>
#include <qtconcurrentrun.h>
#include <QTimer>
#include <QDebug>

CelestialGUI::CelestialGUI(QWidget* parent)
  : QDialog(parent) 
{
  ui.setupUi(this);

  QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel();
  proxyModel->setSourceModel(m_pModel);

  ui.tableView->setSortingEnabled(true);
  ui.tableView->setModel(proxyModel);

  connect(m_pModel, &CStarDataTableModel::dataLoaded, ui.tableView, &QTableView::resizeColumnsToContents);

  connect(m_pModel, &CStarDataTableModel::dataLoaded, [&]() {
    auto catalogs = m_pModel->getStarCatalogNames();
    std::for_each(catalogs.begin(), catalogs.end(), [&](const QString& cat) {
      ui.cb_catalogs->addItem(cat);
    });
  });
   
  QtConcurrent::run(m_pModel, &CStarDataTableModel::loadData);
}
