#include "mindmapnode.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QJsonObject>
#include <QtMath>

MindmapNode::MindmapNode(size_t nodeId, const QString& content, const QBrush& brush, const QPen& pen, const QFont& font):
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

    setContent(content);

    resize();
}

size_t MindmapNode::getNodeId() const
{
    return _nodeId;
}

QJsonValue MindmapNode::toJSON() const
{
    QJsonObject json;
    json["id"] = QVariant(static_cast<unsigned int>(_nodeId)).toInt();
    json["content"] = _content;

    const auto& rect = sceneBoundingRect();

    json["x"] = rect.x();
    json["y"] = rect.y();
    json["w"] = rect.width();
    json["h"] = rect.height();

    return json;
}

void MindmapNode::fromJSON(const QJsonObject &jsonObject)
{
    auto x = jsonObject["x"].toDouble();
    auto y = jsonObject["y"].toDouble();
    auto w = jsonObject["w"].toDouble();
    auto h = jsonObject["h"].toDouble();
    setRect(x, y, w, h);

    setContent(jsonObject["content"].toString());
}

void MindmapNode::setContent(const QString& content)
{
    _content = content;
    _textContainer->setPlainText(_content);
}

QString MindmapNode::getContent() const
{
    return _content;
}

void MindmapNode::resize()
{
    auto _textRect = _textContainer->sceneBoundingRect();
    sceneBoundingRect().setRect(_textRect.x(), _textRect.y(), _textRect.width(), _textRect.height());
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
