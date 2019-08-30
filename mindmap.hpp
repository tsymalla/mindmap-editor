#ifndef MINDMAP_HPP
#define MINDMAP_HPP

#include <QObject>
#include <memory>
#include <unordered_map>
#include "definitions.hpp"
#include "mindmapnode.hpp"
#include "mindmapedge.hpp"

class Mindmap: public QObject
{
    Q_OBJECT
private:
    using NodePtr = std::unique_ptr<MindmapNode>;
    using EdgePtr = std::unique_ptr<MindmapEdge>;
    using NodeMap = std::unordered_map<NodeId, NodePtr>;
    using EdgeMap = std::unordered_map<QString, EdgePtr>;

    NodeMap _nodes;
    EdgeMap _edges;
    NodeId _lastNodeId;

    inline QString _getEdgeId(NodeId nodeFrom, NodeId nodeTo) const;
    void _addEdge(NodeRawPtr nodeFrom, NodeRawPtr nodeTo);

public:
    Mindmap(QObject* parent = nullptr);

    NodeRawPtr addNode();
    NodeRawPtr addNode(const NodeRawPtr parent = nullptr);
    NodeRawPtr addNode(const QString& content, const NodeRawPtr parent = nullptr);
    NodeRawPtr getNodeById(const NodeId id) const;
    int getNodeCount() const;
    bool removeNode(NodeRawPtr node);

    EdgeList getEdgesFromNode(const NodeId nodeId) const;
    EdgeList getAdjacentNodesFromNode(const NodeId nodeId) const;

    void clear();
};

#endif // MINDMAP_HPP
