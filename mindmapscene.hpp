#ifndef MINDMAPSCENE_HPP
#define MINDMAPSCENE_HPP

#include <QGraphicsScene>
#include <unordered_map>
#include <memory>
#include "mindmapnode.hpp"
#include "mindmapedge.hpp"

class MindmapScene : public QGraphicsScene
{
private:
    std::unordered_map<size_t, std::unique_ptr<MindmapNode>> _nodeRects;
    std::unordered_map<std::string, std::unique_ptr<MindmapEdge>> _nodeConnectors;

    QBrush brush;
    QPen pen;
    QFont font;

    std::string _getEdgeId(size_t from, size_t to) const;
    Node* _selectedNode;

public:
    MindmapScene(QObject* parent = nullptr);

public slots:
    void nodeAdded(size_t nodeId, Node* node);
    void edgeAdded(Node* from, Node* to);
    void nodePositionChanged(Node* node);
    void selectionChanged(Node* node);
};

#endif // MINDMAPSCENE_HPP
