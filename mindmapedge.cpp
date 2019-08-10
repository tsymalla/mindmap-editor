#include "mindmapedge.hpp"

MindmapEdge::MindmapEdge(Node *from, Node *to, const QPen& pen): _from(from), _to(to), _pen(pen)
{
    this->setPen(_pen);
    this->setLine(from->getX() + from->getWidth(), from->getY() + from->getHeight(), to->getX(), to->getY());
}

void MindmapEdge::nodePositionUpdated(Node *node, bool isStart)
{
    if (isStart)
    {
        this->setLine(node->getX() + node->getWidth(), node->getY() + node->getHeight(), _to->getX(), _to->getY());
    }
    else
    {
        this->setLine(_from->getX() + _from->getWidth(), _from->getY() + _from->getHeight(), node->getX(), node->getY());
    }
}
