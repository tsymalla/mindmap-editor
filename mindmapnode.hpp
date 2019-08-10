#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include <QGraphicsRectItem>
#include "node.hpp"
#include <QBrush>
#include <QPen>
#include <QFont>

class MindmapNode: public QGraphicsRectItem
{
private:
    size_t _nodeId;
    std::string _content;
    QGraphicsTextItem _textContainer;
    QBrush _brush;
    QPen _pen;
    QFont _font;

public:
    MindmapNode(size_t nodeId, Node* node, const QBrush& brush, const QPen& pen, const QFont& font);

    QGraphicsTextItem* getTextContainer();
public slots:
    void onContentChanged(const std::string& content);
};

#endif // MINDMAPNODE_HPP
