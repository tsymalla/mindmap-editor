#include "mindmapedge.hpp"

MindmapEdge::MindmapEdge(MindmapNode *from, MindmapNode *to, const QPen& pen): _from(from), _to(to), _pen(pen)
{
    this->setPen(_pen);
    const auto& rect = from->boundingRect();
    const auto& rect2 = to->boundingRect();

    this->setLine(rect.x() + rect.width(), rect.y() + rect.height(), rect2.x(), rect2.y());
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
