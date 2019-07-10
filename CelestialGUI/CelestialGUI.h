#pragma once

#include <QtWidgets/QDialog>
#include <QSortFilterProxyModel>
#include "StarDataTableModel.h"
#include "SortProxyModel.h"
#include "ui_CelestialGUI.h"

class CStarDataTableModel;

class CelestialGUI : public QDialog
{
    Q_OBJECT
private:
  Ui::CelestialGUIClass ui;

  CStarDataTableModel* m_pModel { new CStarDataTableModel(this) };
  //QSortFilterProxyModel* m_pProxyModel { new QSortFilterProxyModel() };
  CSortProxyModel* m_pProxyModel { new CSortProxyModel() };

public:
  CelestialGUI(QWidget *parent = nullptr);


};
