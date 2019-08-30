#ifndef MINDMAPNODEGRAPHICSITEM_HPP
#define MINDMAPNODEGRAPHICSITEM_HPP

#include <QObject>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QFont>
#include "definitions.hpp"

class MindmapNodeGraphicsItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    NodeRawPtr _node;
    QGraphicsTextItem *_textContainer;

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

public:
    explicit MindmapNodeGraphicsItem(NodeRawPtr node, QObject *parent = nullptr);

    void resize();

signals:
    void selected(NodeRawPtr node);
    void positionChanged(NodeRawPtr node);
    void doubleClicked(NodeRawPtr node);
};

Q_DECLARE_METATYPE(MindmapNodeGraphicsItem*)

#endif // MINDMAPNODEGRAPHICSITEM_HPP
