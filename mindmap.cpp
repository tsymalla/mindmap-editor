#include "mindmap.hpp"
#include <mutex>

Mindmap::Mindmap(QObject* parent): QObject{parent}, _lastNodeId{0}
{

}

NodeRawPtr Mindmap::addNode(const NodeRawPtr parent)
{
    return addNode("", parent);
}

NodeRawPtr Mindmap::addNode(const QString& content, const NodeRawPtr parent)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    ++_lastNodeId;

    auto actualContent = content;
    if (content.isEmpty())
    {
        actualContent = "Node " + QString::number(_lastNodeId);
    }

    auto node = std::make_unique<MindmapNode>(_lastNodeId, actualContent);

    auto ptr = node.get();
    _nodes.insert(std::make_pair(_lastNodeId, std::move(node)));

    if (parent != nullptr)
    {
        _addEdge(parent, ptr);
    }

    return ptr;
}

NodeRawPtr Mindmap::getNodeById(const NodeId id) const
{
    return (_nodes.at(id)) ? _nodes.at(id).get() : nullptr;
}

int Mindmap::getNodeCount() const
{
    return static_cast<int>(_nodes.size());
}

bool Mindmap::removeNode(NodeRawPtr node)
{
    if (_nodes.size() - 1 == 0)
    {
        return false;
    }

    std::vector<QString> removables;
    for (const auto& edge: _edges)
    {
        auto currentEdge = edge.second.get();

        if (currentEdge->isOutgoingNode(node) || currentEdge->isIncomingNode(node))
        {
            removables.push_back(edge.first);
        }
    }

    for (const auto& removable: removables)
    {
        _edges.erase(removable);
    }

    _nodes.erase(node->getNodeId());
    return true;
}

NodeRawPtr Mindmap::getLastNode() const
{
    return _nodes.begin()->second.get();
}

NodeRawPtr Mindmap::getFirstNode() const
{
    if (!_nodes.empty())
    {
        auto firstNode = _nodes.begin()->second.get();
        return firstNode;
    }

    return nullptr;
}

EdgeList Mindmap::getEdgesFromNode(const NodeId nodeId) const
{

}

EdgeList Mindmap::getAdjacentNodesFromNode(const NodeId nodeId) const
{

}

QString Mindmap::_getEdgeId(NodeId nodeFrom, NodeId nodeTo) const
{
    return QString::number(nodeFrom) + "_" + QString::number(nodeTo);
}

void Mindmap::_addEdge(NodeRawPtr nodeFrom, NodeRawPtr nodeTo)
{
    if (nodeFrom == nullptr || nodeTo == nullptr)
    {
        return;
    }

    auto newEdge = std::make_unique<MindmapEdge>(nodeFrom, nodeTo);
    auto ptr = newEdge.get();

    _edges.insert(std::make_pair(_getEdgeId(nodeFrom->getNodeId(), nodeTo->getNodeId()), std::move(newEdge)));
}

void Mindmap::clear()
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    _nodes.clear();
    _edges.clear();

    _lastNodeId = 0;
}
