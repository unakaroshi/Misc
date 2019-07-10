#include "CelestialGUI.h"
#include "StarCatalog.h"
//#include "FilerProxyModel.h"


#include <QCheckBox>
#include <qtconcurrentrun.h>
#include <QTimer>
#include <QDebug>

CelestialGUI::CelestialGUI(QWidget* parent)
  : QDialog(parent) 
{
  ui.setupUi(this);

  ui.btn_load->setVisible(false);
   
  m_pProxyModel->setSourceModel(m_pModel);

  ui.tableView->setSortingEnabled(true);
  ui.tableView->setModel(m_pProxyModel);
  //ui.tableView->setModel(m_pModel);

  connect(m_pModel, &CStarDataTableModel::dataLoaded, ui.tableView, &QTableView::resizeColumnsToContents);

  connect(m_pModel, &CStarDataTableModel::dataLoaded, [&]() {
    auto catalogs = m_pModel->getStarCatalogNames();
    std::for_each(catalogs.begin(), catalogs.end(), [&](const QString& cat) {
      ui.cb_catalogs->addItem(cat);
    });
   // m_pProxyModel->setSortingColumn(0);

  });

  connect(ui.cb_catalogs, qOverload<const QString&>(&QComboBox::currentTextChanged), [&](const QString& s) {

    qDebug() << s;

   // m_pProxyModel->setFilterKeyColumn(7);
   // m_pProxyModel->setFilterFixedString(s);

  });
   
  QTimer::singleShot(200, [&]() {
    QtConcurrent::run(m_pModel, &CStarDataTableModel::loadData);
  });
  
}
