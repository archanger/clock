#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  a.setApplicationName("Часики");

  QWidget wid;
  MainWindow w(&wid);
  w.show();

  return a.exec();
}
