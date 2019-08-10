#include "mindmapscene.hpp"

MindmapScene::MindmapScene(QObject* parent): QGraphicsScene (parent)
{
    brush.setColor(Qt::green);
    pen.setColor(Qt::black);
    font.setFamily("Arial");
    font.setWeight(20);
}

void MindmapScene::nodeAdded(size_t nodeId, Node *node)
{
    auto newNode = std::make_unique<MindmapNode>(nodeId, node, brush, pen, font);
    auto ptr = newNode.get();
    _nodeRects.insert(std::make_pair(nodeId, std::move(newNode)));

    this->addItem(ptr);
    this->addItem(ptr->getTextContainer());
    update();
}

void MindmapScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{

}
