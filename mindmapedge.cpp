#include "mindmapedge.hpp"

MindmapEdge::MindmapEdge(Node *from, Node *to, const QPen& pen): _from(from), _to(to), _pen(pen)
{
    this->setPen(_pen);
    this->setLine(from->getX() + from->getWidth(), from->getY() + from->getHeight(), to->getX(), to->getY());
}
