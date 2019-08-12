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
    std::unordered_map<size_t, std::unique_ptr<MindmapNode>> _nodes;
    std::unordered_map<std::string, std::unique_ptr<MindmapEdge>> _nodeConnectors;

    QBrush _brush;
    QPen _pen;
    QFont _font;

    std::string _getEdgeId(size_t from, size_t to) const;
    size_t _lastNodeId;

    void _addEdge(MindmapNode* from, MindmapNode* to);

    MindmapNode* _selectedNode;

    void _removeSelectedNodes();

public:
    MindmapScene(QObject* parent = nullptr);
    QString toJSON() const;
    void fromJSON(const QString& json);

    MindmapNode* addNode();
    MindmapNode* addNode(const std::string& content);
    MindmapNode* getNodeById(const size_t id) const;
    size_t getNodeCount() const;

    void reset();

public slots:
    void nodeAdded(MindmapNode* parent);
    void nodePositionChanged(MindmapNode* node);
    void selectionChanged(MindmapNode* node);

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MINDMAPSCENE_HPP
