#include "mindmapedge.hpp"

#include <QVector2D>

void MindmapEdge::_calculateConnectionPoints()
{
    const auto& rect = _from->boundingRect();
    const auto& rect2 = _to->boundingRect();
    QPointF mid(rect.x(), rect.y());
    QPointF mid2(rect2.x(), rect2.y());

    _point1.setX(mid.x());
    _point1.setY(mid.y());
    _point2.setX(mid2.x());
    _point2.setY(mid2.y());
}

MindmapEdge::MindmapEdge(MindmapNode *from, MindmapNode *to, const QPen& pen): _from(from), _to(to), _pen(pen)
{
    this->setPen(_pen);
    _calculateConnectionPoints();

    this->setLine(_point1.x(), _point1.y(), _point2.x(), _point2.y());
}

void MindmapEdge::nodePositionUpdated(MindmapNode *node, bool isStart)
{
    if (isStart)
    {
        const auto& rect = node->boundingRect();
        const auto& rect2 = _to->boundingRect();

        this->setLine(rect.x() + rect.width(), rect.y() + rect.height(), rect2.x(), rect2.y());
    }
    else
    {
        const auto& rect = _from->boundingRect();
        const auto& rect2 = _to->boundingRect();

        this->setLine(rect.x() + rect.width(), rect.y() + rect.height(), rect2.x(), rect2.y());
    }
}
