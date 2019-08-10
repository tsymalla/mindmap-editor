#ifndef MINDMAPEDGE_HPP
#define MINDMAPEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>
#include "node.hpp"

class MindmapEdge: public QGraphicsLineItem
{
private:
    Node* _from;
    Node* _to;
    QPen _pen;
public:
    MindmapEdge(Node* from, Node* to, const QPen& pen);

public slots:
    void nodePositionUpdated(Node* node, bool isStart);
};

#endif // MINDMAPEDGE_HPP
