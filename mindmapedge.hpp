#ifndef MINDMAPEDGE_HPP
#define MINDMAPEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>
#include "mindmapnode.hpp"

class MindmapEdge: public QGraphicsLineItem
{
private:
    NodeRawPtr _nodeFrom;
    NodeRawPtr _nodeTo;
    QPointF _point1;
    QPointF _point2;

    void _calculateConnectionPoints();
public:
    MindmapEdge(NodeRawPtr nodeFrom, NodeRawPtr nodeTo);

    bool isOutgoingNode(NodeRawPtr nodeFrom) const;
    bool isIncomingNode(NodeRawPtr nodeTo) const;

    void redraw();
};

#endif // MINDMAPEDGE_HPP
