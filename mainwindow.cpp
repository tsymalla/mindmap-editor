#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mindmapScene = new MindmapScene(this);
    ui->mindmapView->setScene(mindmapScene);

    connect(this, &MainWindow::nodeAdded, mindmapScene, &MindmapScene::nodeAdded);
    connect(this, &MainWindow::edgeAdded, mindmapScene, &MindmapScene::edgeAdded);

    _root = _graph.addNode("Mindmap");
    emit(nodeAdded(_root, _graph.getNode(_root)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Node_triggered()
{
    auto id2 = _graph.addNode();

    _graph.connectNodes(_root, id2);

    emit(nodeAdded(id2, _graph.getNode(id2)));
    emit(edgeAdded(_graph.getNode(_root), _graph.getNode(id2)));
}

void MainWindow::on_action_Exit_triggered()
{
    QMessageBox confirm;
    confirm.setInformativeText("The mindmap has been changed.");
    confirm.setText("Do you want to save your changes?");
    confirm.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    auto ret = confirm.exec();

    if (ret == QMessageBox::Save || ret == QMessageBox::Discard)
    {
        QApplication::exit();
    }
}

void MainWindow::on_action_Save_triggered()
{
    auto fileName = QFileDialog::getSaveFileName(this, tr("Save file..."), QDir::currentPath(), tr("SimpleMind files (*.mmp)"));

    if (!fileName.isNull())
    {
        if (!fileName.endsWith(tr(".mmp")))
        {
            fileName += ".mmp";
        }

        QFile file(fileName);

        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            stream << _graph.toJSON();
            file.close();
        }
    }
}
