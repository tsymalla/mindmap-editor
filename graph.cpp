#include "graph.hpp"
#include <mutex>

Graph::Graph()
{
}

Graph::~Graph()
{
    _edges.clear();
    _nodes.clear();
}

void Graph::connectNodes(size_t from, size_t to)
{
    if (getNode(from) == nullptr || getNode(to) == nullptr)
    {
        return;
    }

    auto edge = std::make_unique<Edge>(from, to, "");
    _edges.push_back(std::move(edge));
}

size_t Graph::addNode(const std::string &content)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    ++_lastNode;

    auto node = std::make_unique<Node>(content);
    _nodes.insert(std::make_pair(_lastNode, std::move(node)));

    return _lastNode;
}

Node *Graph::getNode(const size_t id) const
{
    return (_nodes.at(id) != nullptr) ? _nodes.at(id).get() : nullptr;
}
