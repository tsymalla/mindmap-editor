#ifndef MINDMAPSCENE_HPP
#define MINDMAPSCENE_HPP

#include <QGraphicsScene>
#include <unordered_map>
#include <memory>
#include "mindmapnode.hpp"
#include "mindmapedge.hpp"

class MindmapScene : public QGraphicsScene
{
    Q_OBJECT
private:
    std::unordered_map<size_t, std::unique_ptr<MindmapNode>> _nodes;
    std::unordered_map<std::string, std::unique_ptr<MindmapEdge>> _nodeConnectors;

    QBrush _backgroundBrush;
    QBrush _brush;
    QPen _pen;
    QFont _font;

    std::string _getEdgeId(size_t from, size_t to) const;
    size_t _lastNodeId;

    void _addEdge(MindmapNode* from, MindmapNode* to);

    MindmapNode* _selectedNode;

public:
    MindmapScene(QObject* parent = nullptr);
    QString toJSON() const;
    void fromJSON(const QString& json);

    MindmapNode* addNode();
    MindmapNode* addNode(const QString& content);
    MindmapNode* getNodeById(const size_t id) const;
    int getNodeCount() const;
    void removeSelectedNodes();
    void changeNodeContent(MindmapNode* node, const QString& content);

    void reset();

public slots:
    void nodePositionChanged(MindmapNode* node);
    void selectionChanged(MindmapNode* node);
    void nodeDoubleClick(MindmapNode* node);

signals:
    void passNodeDoubleClick(MindmapNode* node);
    void notifyMindmapChanged(bool wasSaved);

protected:
    void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // MINDMAPSCENE_HPP
