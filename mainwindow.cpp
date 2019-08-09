#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent) :
                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mindmapScene = new QGraphicsScene(this);
    ui->mindmapView->setScene(mindmapScene);

    auto id = _graph.addNode("Mindmap");
    auto id2 = _graph.addNode("Test");

    _graph.connectNodes(id, id2);
    _drawMindmap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_drawMindmap()
{
    mindmapScene->clear();
    QBrush greenBrush(Qt::green);
    QPen outlinePen(Qt::black);
    QFont font("Arial", 14);

    outlinePen.setWidth(2);

    for (const auto& node: _graph.getNodes())
    {
        Node* currentNode = node.second.get();

        auto fromRect = mindmapScene->addRect(currentNode->getX(), currentNode->getY(), currentNode->getWidth(), currentNode->getHeight(), outlinePen, greenBrush);
        fromRect->setFlag(QGraphicsItem::ItemIsMovable);
    }

    for (const auto& edge: _graph.getEdges())
    {
        Node* from = _graph.getNode(edge->getFrom());
        Node* to = _graph.getNode(edge->getTo());

        auto fromText = mindmapScene->addText(QString::fromStdString(from->getContent()), font);
        fromText->setPos(from->getX(), from->getY());

        auto toText = mindmapScene->addText(QString::fromStdString(to->getContent()), font);
        toText->setPos(to->getX(), to->getY());

        auto connector = mindmapScene->addLine(from->getX() + from->getWidth(), from->getY() + from->getHeight(), to->getX(), to->getY(), outlinePen);
    }
}

void MainWindow::on_actionAdd_Node_triggered()
{
    auto id = _graph.getLatestNode();
    auto id2 = _graph.addNode();

    _graph.connectNodes(id, id2);
    _drawMindmap();
}
