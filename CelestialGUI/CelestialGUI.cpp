#include "CelestialGUI.h"
#include "StarCatalog.h"
//#include "FilerProxyModel.h"

#include <QSortFilterProxyModel>
#include <QDebug>

CelestialGUI::CelestialGUI(QWidget *parent)
  : QDialog(parent)
{
    ui.setupUi(this);
    
    QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    //CFilterProxyModel* proxyModel = new CFilterProxyModel();
    proxyModel->setSourceModel(m_pModel);
   // proxyModel->setFilterRegExp(QRegExp("SAO", Qt::CaseInsensitive,QRegExp::FixedString));
   // proxyModel->setFilterKeyColumn(0);
      
    ui.tableView->setSortingEnabled(true);
    ui.tableView->setModel(proxyModel);
    //ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);

    connect(m_pModel, &CStarDataTableModel::dataLoaded, [&]() {
      ui.tableView->resizeColumnsToContents();
    });
    

    connect(ui.btn_load, &QPushButton::clicked, m_pModel, &CStarDataTableModel::loadCatalogs);
 }
