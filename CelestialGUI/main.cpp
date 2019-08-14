#include "CelestialGUI.h"
#include <QtWidgets/QApplication> // NOLINT

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  CelestialGUI w;
  w.show();
  return a.exec();
}
