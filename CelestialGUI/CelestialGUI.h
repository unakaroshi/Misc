#pragma once

#include <QtWidgets/QDialog>
#include "StarDataTableModel.h"
#include "ui_CelestialGUI.h"

class CStarDataTableModel;

class CelestialGUI : public QDialog
{
    Q_OBJECT
private:
  Ui::CelestialGUIClass ui;

  CStarDataTableModel* m_pModel { new CStarDataTableModel(this) };

public:
  CelestialGUI(QWidget *parent = nullptr);


};
