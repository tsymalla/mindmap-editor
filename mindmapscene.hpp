#ifndef MINDMAPSCENE_HPP
#define MINDMAPSCENE_HPP

#include <QGraphicsScene>
#include "mindmap.hpp"

class MindmapScene : public QGraphicsScene
{
    Q_OBJECT
private:
    QBrush _backgroundBrush;
    QBrush _brush;
    QPen _pen;
    QFont _font;

    NodeRawPtr _selectedNode;
    Mindmap _mindmap;

public:
    MindmapScene(QObject* parent = nullptr);
    QString toJSON() const;
    void fromJSON(const QString& json);

    void removeSelectedNodes();
    void changeNodeContent(NodeRawPtr node, const QString& content);

    void reset();

public slots:
    void nodePositionChanged(NodeRawPtr node);
    void selectionChanged(NodeRawPtr node);
    void nodeDoubleClick(NodeRawPtr node);

signals:
    void passNodeDoubleClick(NodeRawPtr node);
    void notifyMindmapChanged(bool wasSaved);

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MINDMAPSCENE_HPP
