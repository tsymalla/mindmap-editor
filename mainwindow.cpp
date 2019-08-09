#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto id = _graph.addNode("Root");
    auto id2 = _graph.addNode("Sepp");

    _graph.connectNodes(id, id2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
