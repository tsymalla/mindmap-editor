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

    _mindmapScene = new MindmapScene(this);
    ui->mindmapView->setScene(_mindmapScene);

    _about = new About(this);

    connect(this, &MainWindow::nodeAdded, _mindmapScene, &MindmapScene::nodeAdded);

    _root = _mindmapScene->addNode("Mindmap");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAdd_Node_triggered()
{
    emit nodeAdded(_root);
    ui->statusBar->showMessage(tr("%n nodes in mind map.", "", _mindmapScene->getNodeCount()));
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
            stream << _mindmapScene->toJSON();
            file.close();
        }
    }
}

void MainWindow::on_action_New_Mindmap_triggered()
{
    _mindmapScene->reset();

    _root = _mindmapScene->addNode("Mindmap");
}

void MainWindow::on_action_About_triggered()
{
    _about->show();
}

void MainWindow::on_action_Open_file_triggered()
{
    auto fileName = QFileDialog::getOpenFileName(this, tr("Open file..."), QDir::currentPath(), tr("SimpleMind files (*.mmp)"));

    if (!fileName.isNull())
    {
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&file);
            QString data = stream.readAll();
            _mindmapScene->fromJSON(data);
            file.close();
        }
    }
}
