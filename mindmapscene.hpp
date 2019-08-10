#ifndef MINDMAPSCENE_HPP
#define MINDMAPSCENE_HPP

#include <QGraphicsScene>
#include <unordered_map>
#include <memory>
#include "mindmapnode.hpp"

class MindmapScene : public QGraphicsScene
{
private:
    std::unordered_map<size_t, std::unique_ptr<MindmapNode>> _nodeRects;

    QBrush brush;
    QPen pen;
    QFont font;

public:
    MindmapScene(QObject* parent = nullptr);

public slots:
    void nodeAdded(size_t nodeId, Node* node);
protected:
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // MINDMAPSCENE_HPP
