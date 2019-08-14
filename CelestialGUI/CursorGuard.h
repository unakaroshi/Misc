#pragma once

#include <QApplication>

class CursorGuard {
 public:
  CursorGuard(QCursor cursor = Qt::WaitCursor) {
    QApplication::setOverrideCursor(cursor);
  }

  ~CursorGuard() { QApplication::restoreOverrideCursor(); }
};
