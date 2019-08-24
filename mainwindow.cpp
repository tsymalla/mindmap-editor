#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _mindmapScene = new MindmapScene(this);
    ui->mindmapView->setScene(_mindmapScene);

    _about = new About(this);

    connect(_mindmapScene, &MindmapScene::passNodeDoubleClick, this, &MainWindow::passNodeDoubleClick);
    _mindmapScene->addNode("Mindmap");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::passNodeDoubleClick(MindmapNode *node)
{
    auto _newContent = QInputDialog::getText(this, "Content", "Set content of the node", QLineEdit::Normal, node->getContent());
    _mindmapScene->changeNodeContent(node, _newContent);
}

void MainWindow::on_actionAdd_Node_triggered()
{
    _mindmapScene->addNode();
    ui->statusBar->showMessage(tr("%n nodes in mind map.", "", _mindmapScene->getNodeCount()));
}

void MainWindow::on_action_Exit_triggered()
{
    auto button = QMessageBox::information(this, tr("The mindmap has been changed."), tr("Do you want to save your changes?"), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (button == QMessageBox::Save || button == QMessageBox::Discard)
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

void MainWindow::on_actionRemove_node_triggered()
{
    _mindmapScene->removeSelectedNodes();
}

void MainWindow::on_actionExport_triggered()
{
    auto fileName = QFileDialog::getSaveFileName(this, tr("Export mindmap to image..."), QDir::currentPath(), tr("Image files (*.png *.jpg *.bmp)"));

    if (!fileName.isNull())
    {
        const auto& sceneRect = _mindmapScene->sceneRect();

        QSize sceneRectSize {static_cast<int>(sceneRect.width()), static_cast<int>(sceneRect.height())};
        QImage exportImage(sceneRectSize, QImage::Format_ARGB32);
        exportImage.fill(Qt::transparent);

        QPainter painter(&exportImage);

        painter.setRenderHint(QPainter::Antialiasing);
        _mindmapScene->render(&painter);

        if (exportImage.save(fileName))
        {
            QMessageBox::information(this, tr("Success"), QString("Image successfully saved to path " + fileName + "."));
        }
        else
        {
            QMessageBox::warning(this, tr("Export failed"), tr("Could not save image to file."));
        }
    }
}
