#include "mindmapedge.hpp"

#include <QVector2D>
#include <vector>

void MindmapEdge::_calculateConnectionPoints()
{
    if (_from == nullptr || _to == nullptr)
    {
        return;
    }

    const auto& rect = _from->sceneBoundingRect();
    const auto& rect2 = _to->sceneBoundingRect();

    std::vector<QPointF> _edgePoints1 = {
        {rect.x(), rect.y()},
        {rect.x() + rect.width(), rect.y()},
        {rect.x(), rect.y() + rect.height()},
        {rect.x() + rect.width(), rect.y() + rect.height()}
    };

    std::vector<QPointF> _edgePoints2 = {
        {rect2.x(), rect2.y()},
        {rect2.x() + rect2.width(), rect2.y()},
        {rect2.x(), rect2.y() + rect2.height()},
        {rect2.x() + rect2.width(), rect2.y() + rect2.height()}
    };

    auto minPoint1 = _edgePoints1[0];
    auto minPoint2 = _edgePoints2[0];
    QVector2D vec1(minPoint1);
    QVector2D vec2(minPoint2);
    float minDistance = vec1.distanceToPoint(vec2);
    _point1 = minPoint1;
    _point2 = minPoint2;

    for (size_t i = 0; i < _edgePoints1.size(); ++i)
    {
        vec1 = QVector2D(_edgePoints1[i]);

        for (size_t j = 0; j < _edgePoints2.size(); ++j)
        {
            vec2 = QVector2D(_edgePoints2[j]);

            const auto currentDistance = qAbs(vec1.distanceToPoint(vec2));
            if (currentDistance < minDistance)
            {
                minDistance = currentDistance;
                _point1 = _edgePoints1[i];
                _point2 = _edgePoints2[j];
            }
        }
    }
}

void MindmapEdge::redraw()
{
    _calculateConnectionPoints();
    setLine(_point1.x(), _point1.y(), _point2.x(), _point2.y());
}

MindmapEdge::MindmapEdge(MindmapNode *from, MindmapNode *to, const QPen& pen): _from(from), _to(to), _pen(pen)
{
    setPen(_pen);
    redraw();
}

bool MindmapEdge::isFrom(MindmapNode *from) const
{
    return _from->getNodeId() == from->getNodeId();
}

bool MindmapEdge::isTo(MindmapNode *to) const
{
    return _to->getNodeId() == to->getNodeId();
}
