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
    auto sin = qRadiansToDegrees(qSin(qreal(_nodeId)));
    auto cos = qRadiansToDegrees(qCos(qreal(_nodeId)));

    setRect(cos * 4.0,
            sin * 4.0,
            120.0,
            40.0);

    setFlag(QGraphicsItem::ItemIsMovable);
    setBrush(_brush);

    setPen(_pen);

    _textContainer = new QGraphicsTextItem(this);
    _textContainer->setPos(sceneBoundingRect().x(), sceneBoundingRect().y());

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

    const auto& rect = sceneBoundingRect();

    json["x"] = rect.x();
    json["y"] = rect.y();
    json["w"] = rect.width();
    json["h"] = rect.height();

    return json;
}

void MindmapNode::setContent(const std::string &content)
{
    onContentChanged(content);
}

std::string MindmapNode::getContent() const
{
    return _content;
}

void MindmapNode::onContentChanged(const std::string &content)
{
    _content = content;
    _textContainer->setPlainText(QString::fromStdString(_content));
}

void MindmapNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // emit signal to the mindmap scene which will then re-calculate the corresponding edges
    emit positionChanged(this);

    // propagate event to the base object to prevent jumping of the rect
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void MindmapNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit nodeSelected(this);
}

void MindmapNode::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit nodeDoubleClick(this);
}
