#include "mindmapnode.hpp"
#include <QGraphicsSceneDragDropEvent>
#include <QDebug>
#include <QJsonObject>
#include <QtMath>

MindmapNode::MindmapNode(NodeId nodeId, const QString& content):
    _nodeId(nodeId)
{
    setContent(content);

    //
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

    /*const auto& rect = sceneBoundingRect();

    json["x"] = rect.x();
    json["y"] = rect.y();
    json["w"] = rect.width();
    json["h"] = rect.height();*/

    return json;
}

void MindmapNode::fromJSON(const QJsonObject &jsonObject)
{
    auto x = jsonObject["x"].toDouble();
    auto y = jsonObject["y"].toDouble();
    auto w = jsonObject["w"].toDouble();
    auto h = jsonObject["h"].toDouble();
    //setRect(x, y, w, h);

    setContent(jsonObject["content"].toString());
}

void MindmapNode::setContent(const QString& content)
{
    _content = content;
    //_textContainer->setPlainText(_content);
}

QString MindmapNode::getContent() const
{
    return _content;
}
