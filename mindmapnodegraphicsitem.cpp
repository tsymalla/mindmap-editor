#include "mindmapnodegraphicsitem.hpp"
#include "mindmapnode.hpp"
#include <assert.h>
#include <QtMath>

MindmapNodeGraphicsItem::MindmapNodeGraphicsItem(NodeRawPtr node, QObject *parent) : QObject(parent), _node(node)
{
    assert(node != nullptr);

    setRect(_node->getX(), _node->getY(), _node->getWidth(), _node->getHeight());
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable);

    _textContainer = new QGraphicsTextItem(this);

    _textContainer->setPos(_node->getX(), _node->getY());
    changeNodeContent(node->getContent());

    resize();

    _synchronizePositionChange();
}

void MindmapNodeGraphicsItem::changeNodeContent(const QString &content)
{
    _node->setContent(content);
    _textContainer->setPlainText(_node->getContent());
}

void MindmapNodeGraphicsItem::resize()
{
    auto _textRect = _textContainer->sceneBoundingRect();
    sceneBoundingRect().setRect(_textRect.x(), _textRect.y(), _textRect.width(), _textRect.height());
}

void MindmapNodeGraphicsItem::_synchronizePositionChange()
{
    // synchronize change to the actual node
    const auto& sceneRect = sceneBoundingRect();

    _node->setBoundaries(sceneRect.x(), sceneRect.y(), sceneRect.width(), sceneRect.height());
}

void MindmapNodeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    _synchronizePositionChange();

    // emit signal to the mindmap scene which will then re-calculate the corresponding edges
    emit positionChanged(this, _node);

    // propagate event to the base object to prevent jumping of the rect
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void MindmapNodeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit selected(this, _node);
}

void MindmapNodeGraphicsItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit doubleClicked(this, _node);
}
