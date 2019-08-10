#include "mindmapnode.hpp"

MindmapNode::MindmapNode(size_t nodeId, Node *node, QBrush brush, QPen pen, QFont font): _nodeId(nodeId)
{
    _brush = brush;
    _pen = pen;
    _font = font;

    onContentChanged(node->getContent());

    setRect(node->getX(), node->getY(), node->getWidth(), node->getHeight());
    setFlag(QGraphicsItem::ItemIsMovable);
    setBrush(brush);
    setPen(pen);

    _textContainer.setPos(node->getX(), node->getY());
}

QGraphicsTextItem* MindmapNode::getTextContainer()
{
    return &_textContainer;
}

void MindmapNode::onContentChanged(const std::string &content)
{
    _content = content;
    _textContainer.setPlainText(QString::fromStdString(_content));
}
