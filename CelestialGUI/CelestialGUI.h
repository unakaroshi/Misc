#pragma once

#include "StarDataTableModel.h"
//#define USE_QT_PROXY 1

#if defined (USE_QT_PROXY)
#  include <QSortFilterProxyModel>
#else
#  include "SortProxyModel.h"
#endif

#include "ui_CelestialGUI.h" // NOLINT


class CelestialGUI : public QDialog
{
    Q_OBJECT
private:
  Ui::CelestialGUIClass ui;

  CStarDataTableModel* m_pModel { new CStarDataTableModel(this) };
  
  
#if defined (USE_QT_PROXY)

  QSortFilterProxyModel* m_pProxyModel { new QSortFilterProxyModel() };
#else
  CSortProxyModel* m_pProxyModel { new CSortProxyModel() };
#endif

public:
  explicit CelestialGUI(QWidget *parent = nullptr);
  ~CelestialGUI() = default;

  CelestialGUI(const CelestialGUI&) = delete;
  CelestialGUI(CelestialGUI&&) = delete;
  CelestialGUI& operator=(const CelestialGUI&) = delete;

};
