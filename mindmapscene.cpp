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

    addItem(ptr);
    addItem(ptr->getTextContainer());

    update();
}

void MindmapScene::edgeAdded(Node *from, Node *to)
{
    auto newEdge = std::make_unique<MindmapEdge>(from, to, pen);
    auto ptr = newEdge.get();

    _nodeConnectors.insert(std::make_pair(_getEdgeId(from->getId(), to->getId()), std::move(newEdge)));

    addItem(ptr);

    update();
}

std::string MindmapScene::_getEdgeId(size_t from, size_t to) const
{
    return std::to_string(from) + "_" + std::to_string(to);
}

void MindmapScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{

}
