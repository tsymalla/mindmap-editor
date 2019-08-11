#include "mindmapnode.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QJsonObject>
#include <QtMath>

MindmapNode::MindmapNode(size_t nodeId, const std::string& content, const QBrush& brush, const QPen& pen, const QFont& font):
    _nodeId(nodeId),
    _brush(brush),
    _pen(pen),
    _font(font)
{
    setRect(qCos(qreal(_nodeId)) * 250.0,
            qSin(qreal(_nodeId)) * 250.0,
            120.0,
            40.0);

    setFlag(QGraphicsItem::ItemIsMovable);
    setBrush(_brush);

    setPen(_pen);

    _textContainer = new QGraphicsTextItem(this);
    _textContainer->setPos(boundingRect().x(), boundingRect().y());

    onContentChanged(content);
}

size_t MindmapNode::getNodeId() const
{
    return _nodeId;
}

QJsonValue MindmapNode::toJSON() const
{
    QJsonObject json;
    json["id"] = QVariant(static_cast<unsigned int>(_nodeId)).toInt();
    json["content"] = QString::fromStdString(_content);

    const auto& rect = boundingRect();

    json["x"] = rect.x();
    json["y"] = rect.y();
    json["w"] = rect.width();
    json["h"] = rect.height();

    return json;
}

void MindmapNode::onContentChanged(const std::string &content)
{
    _content = content;
    _textContainer->setPlainText(QString::fromStdString(_content));
}

void MindmapNode::onPositionChanged(qreal newX, qreal newY)
{
}

void MindmapNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    auto pos = event->pos();

    emit onPositionChanged(pos.x(), pos.y());
}

void MindmapNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit nodeSelected(this);
}
