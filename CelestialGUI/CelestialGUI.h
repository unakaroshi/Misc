#pragma once


#include "SortProxyModel.h"
#include "StarDataTableModel.h"

#include "ui_CelestialGUI.h" // NOLINT


class CelestialGUI : public QDialog
{
    Q_OBJECT
private:
  Ui::CelestialGUIClass ui;

  CStarDataTableModel* m_pModel { new CStarDataTableModel(this) };
  
  CSortProxyModel* m_pProxyModel { new CSortProxyModel() };

public:
  explicit CelestialGUI(QWidget *parent = nullptr);
  ~CelestialGUI() = default;

  CelestialGUI(const CelestialGUI&) = delete;
  CelestialGUI(CelestialGUI&&) = delete;
  CelestialGUI& operator=(const CelestialGUI&) = delete;

};
