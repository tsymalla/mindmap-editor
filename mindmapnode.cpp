#include "mindmapnode.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>

MindmapNode::MindmapNode(size_t nodeId, Node *node, const QBrush& brush, const QPen& pen, const QFont& font): _nodeId(nodeId),
                                                                                                              _node(node),
                                                                                                              _brush(brush),
                                                                                                              _pen(pen),
                                                                                                              _font(font)
{
    _textContainer = new QGraphicsTextItem(this);
    _textContainer->setPos(node->getX(), node->getY());

    onContentChanged(node->getContent());

    setRect(node->getX(), node->getY(), node->getWidth(), node->getHeight());
    setFlag(QGraphicsItem::ItemIsMovable);
    setBrush(brush);

    setPen(pen);
}

QGraphicsTextItem* MindmapNode::getTextContainer()
{
    return _textContainer;
}

void MindmapNode::onContentChanged(const std::string &content)
{
    _content = content;
    _textContainer->setPlainText(QString::fromStdString(_content));
}

void MindmapNode::onPositionChanged(qreal newX, qreal newY)
{
    _node->setX(newX);
    _node->setY(newY);
}

void MindmapNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos = event->pos();

    emit onPositionChanged(pos.x(), pos.y());
}
