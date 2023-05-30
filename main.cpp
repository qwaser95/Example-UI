#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication application(argc, argv);
  MainWindow window;
  window.setGeometry(
    QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        window.size(),
        qApp->desktop()->availableGeometry()
              )
        );
  window.show();
  return application.exec();
}
