#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_DisableWindowContextHelpButton);

    MainWindow w;
    w.show();

    return a.exec();
}
