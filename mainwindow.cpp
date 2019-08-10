#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mindmapScene = new MindmapScene(this);
    ui->mindmapView->setScene(mindmapScene);

    _root = _graph.addNode("Mindmap");
    auto id2 = _graph.addNode();

    _graph.connectNodes(_root, id2);

    connect(this, &MainWindow::nodeAdded, mindmapScene, &MindmapScene::nodeAdded);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_drawMindmap()
{

    for (const auto& edge: _graph.getEdges())
    {
        Node* from = _graph.getNode(edge->getFrom());
        Node* to = _graph.getNode(edge->getTo());

        /*auto fromText = mindmapScene->addText(QString::fromStdString(from->getContent()), font);
        fromText->setPos(from->getX(), from->getY());

        auto toText = mindmapScene->addText(QString::fromStdString(to->getContent()), font);
        toText->setPos(to->getX(), to->getY());

        auto connector = mindmapScene->addLine(from->getX() + from->getWidth(), from->getY() + from->getHeight(), to->getX(), to->getY(), outlinePen);*/
    }
}

void MainWindow::on_actionAdd_Node_triggered()
{
    auto id2 = _graph.addNode();

    _graph.connectNodes(_root, id2);

    emit(nodeAdded(id2, _graph.getNode(id2)));
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
