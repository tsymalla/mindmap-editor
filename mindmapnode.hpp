#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include "definitions.hpp"

class MindmapNode: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    NodeId _nodeId;
    QString _content;
    QGraphicsTextItem *_textContainer;

public:
    MindmapNode(NodeId nodeId,
                const QString& content);

    NodeId getNodeId() const;

    QJsonValue toJSON() const;
    void fromJSON(const QJsonObject& jsonObject);
    void setContent(const QString& content);
    QString getContent() const;

    void resize();

signals:
    void nodeSelected(MindmapNode* node);
    void positionChanged(MindmapNode* node);
    void nodeDoubleClick(MindmapNode* node);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

Q_DECLARE_METATYPE(MindmapNode*)

#endif // MINDMAPNODE_HPP
