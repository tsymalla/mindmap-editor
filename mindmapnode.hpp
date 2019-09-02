#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include "definitions.hpp"

#include <QObject>
#include <QJsonValue>
#include "jsonserializable.hpp"

class MindmapNode: public QObject, public JSONSerializable
{
    Q_OBJECT
private:
    NodeId _nodeId;
    QString _content;

    qreal _x;
    qreal _y;
    qreal _width;
    qreal _height;

public:
    MindmapNode(NodeId nodeId,
                const QString& content);
    ~MindmapNode() override;

    NodeId getNodeId() const;

    void setContent(const QString& content);
    QString getContent() const;

    qreal getX() const;
    void setX(qreal x);

    qreal getY() const;
    void setY(qreal y);

    qreal getWidth() const;
    void setWidth(qreal width);

    qreal getHeight() const;
    void setHeight(qreal height);

    void setBoundaries(qreal x, qreal y, qreal width, qreal height);

    QJsonValue toJSON() const override;
    void fromJSON(const QJsonValue &json) override;
};

Q_DECLARE_METATYPE(MindmapNode*)

#endif // MINDMAPNODE_HPP
