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
public:
    MindmapEdge(MindmapNode* from, MindmapNode* to, const QPen& pen);

public slots:
    void nodePositionUpdated(MindmapNode* node, bool isStart);
};

#endif // MINDMAPEDGE_HPP
