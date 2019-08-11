#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QFont>

class MindmapNode: public QGraphicsRectItem
{
private:
    size_t _nodeId;
    std::string _content;
    QGraphicsTextItem *_textContainer;
    QBrush _brush;
    QPen _pen;
    QFont _font;

public:
    MindmapNode(size_t nodeId,
                const std::string& content,
                const QBrush& brush,
                const QPen& pen,
                const QFont& font);

    size_t getNodeId() const;

    QJsonValue toJSON() const;
public slots:
    void onContentChanged(const std::string& content);

private slots:
    void onPositionChanged(qreal newX, qreal newY);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MINDMAPNODE_HPP
