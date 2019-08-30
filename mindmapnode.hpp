#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include "definitions.hpp"

#include <QObject>
#include <QJsonValue>

class MindmapNode: public QObject
{
    Q_OBJECT
private:
    NodeId _nodeId;
    QString _content;

public:
    MindmapNode(NodeId nodeId,
                const QString& content);

    NodeId getNodeId() const;

    QJsonValue toJSON() const;
    void fromJSON(const QJsonObject& jsonObject);

    void setContent(const QString& content);
    QString getContent() const;
};

Q_DECLARE_METATYPE(MindmapNode*)

#endif // MINDMAPNODE_HPP
