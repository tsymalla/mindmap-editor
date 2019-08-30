#include "mindmapnodegraphicsitem.hpp"
#include "mindmapnode.hpp"
#include <assert.h>
#include <QtMath>

MindmapNodeGraphicsItem::MindmapNodeGraphicsItem(NodeRawPtr node, QObject *parent) : QObject(parent), _node(node)
{
    assert(node != nullptr);

    auto nodeId = node->getNodeId();
    auto sin = qRadiansToDegrees(qSin(qreal(nodeId)));
    auto cos = qRadiansToDegrees(qCos(qreal(nodeId)));

    setRect(cos * 4.0,
            sin * 4.0,
            120.0,
            40.0);

    setFlag(QGraphicsItem::ItemIsMovable);
    /*setBrush(_brush);

    setPen(_pen);*/

    _textContainer = new QGraphicsTextItem(this);
    _textContainer->setPos(sceneBoundingRect().x(), sceneBoundingRect().y());

    resize();
}

void MindmapNodeGraphicsItem::resize()
{
    auto _textRect = _textContainer->sceneBoundingRect();
    sceneBoundingRect().setRect(_textRect.x(), _textRect.y(), _textRect.width(), _textRect.height());
}

void MindmapNodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // emit signal to the mindmap scene which will then re-calculate the corresponding edges
    emit positionChanged(_node);

    // propagate event to the base object to prevent jumping of the rect
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void MindmapNodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit selected(_node);
}

void MindmapNodeGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit doubleClicked(_node);
}
