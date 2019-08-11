#ifndef MINDMAPNODE_HPP
#define MINDMAPNODE_HPP

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include <QFont>

class MindmapNode: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
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

signals:
    void nodeSelected(MindmapNode* node);

protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

Q_DECLARE_METATYPE(MindmapNode*)

#endif // MINDMAPNODE_HPP
