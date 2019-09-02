#include "mindmapnode.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QJsonObject>
#include <QtMath>

MindmapNode::MindmapNode(NodeId nodeId, const QString& content):
    _nodeId(nodeId)
{
    setContent(content);

    auto sin = qRadiansToDegrees(qSin(qreal(_nodeId)));
    auto cos = qRadiansToDegrees(qCos(qreal(_nodeId)));

    setBoundaries(cos * 4.0, sin * 4.0, 120.0, 40.0);
}

MindmapNode::~MindmapNode()
{

}

NodeId MindmapNode::getNodeId() const
{
    return _nodeId;
}

QJsonValue MindmapNode::toJSON() const
{
    QJsonObject json;
    json["id"] = QVariant(static_cast<unsigned int>(_nodeId)).toInt();
    json["content"] = _content;

    json["x"] = _x;
    json["y"] = _y;
    json["w"] = _width;
    json["h"] = _height;

    return json;
}

void MindmapNode::fromJSON(const QString &json)
{
    QJsonObject jsonObject = QJsonValue(json).toObject();

    auto x = jsonObject["x"].toDouble();
    auto y = jsonObject["y"].toDouble();
    auto w = jsonObject["w"].toDouble();
    auto h = jsonObject["h"].toDouble();

    setBoundaries(x, y, w, h);

    setContent(jsonObject["content"].toString());
}

void MindmapNode::setContent(const QString& content)
{
    _content = content;
}

QString MindmapNode::getContent() const
{
    return _content;
}

qreal MindmapNode::getX() const
{
    return _x;
}

void MindmapNode::setX(qreal x)
{
    _x = x;
}

qreal MindmapNode::getY() const
{
    return _y;
}

void MindmapNode::setY(qreal y)
{
    _y = y;
}

qreal MindmapNode::getWidth() const
{
    return _width;
}

void MindmapNode::setWidth(qreal width)
{
    _width = width;
}

qreal MindmapNode::getHeight() const
{
    return _height;
}

void MindmapNode::setHeight(qreal height)
{
    _height = height;
}

void MindmapNode::setBoundaries(qreal x, qreal y, qreal width, qreal height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
}
