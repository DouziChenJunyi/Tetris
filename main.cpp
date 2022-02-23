#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/6,(QApplication::desktop()->height() - w.height())/6 + 50);
    return a.exec();
}
