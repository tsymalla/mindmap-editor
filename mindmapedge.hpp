#ifndef MINDMAPEDGE_HPP
#define MINDMAPEDGE_HPP

#include <QGraphicsLineItem>
#include <QPen>
#include "mindmapnode.hpp"

class MindmapEdge: public QGraphicsLineItem
{
private:
    MindmapNode* _from;
    MindmapNode* _to;
    QPen _pen;
    QPointF _point1;
    QPointF _point2;

    void _calculateConnectionPoints();
public:
    MindmapEdge(MindmapNode* from, MindmapNode* to, const QPen& pen);

    bool isFrom(MindmapNode* from) const;
    bool isTo(MindmapNode* to) const;

    void redraw();
};

#endif // MINDMAPEDGE_HPP
