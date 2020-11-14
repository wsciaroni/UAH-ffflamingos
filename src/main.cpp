#include "determineroledialog.h"

#include <QApplication>

int main(int argc, char* argv[]) {
  QApplication a(argc, argv);
  DetermineRoleDialog d;
  d.show();
  return a.exec();
}
