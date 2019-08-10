#include "graph.hpp"
#include <mutex>
#include <cmath>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Graph::Graph(): _lastNode(0)
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

size_t Graph::addNode()
{
    return addNode("");
}

size_t Graph::addNode(const std::string &content)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    ++_lastNode;

    auto actualContent = content;
    if (content.empty())
    {
        actualContent = "Node " + std::to_string(_lastNode);
    }

    auto node = std::make_unique<Node>(_lastNode, actualContent);
    node->setX(std::cos(static_cast<double>(_lastNode)) * 250.0);
    node->setY(std::sin(static_cast<double>(_lastNode)) * 250.0);
    node->setWidth(120.0);
    node->setHeight(40.0);

    _nodes.insert(std::make_pair(_lastNode, std::move(node)));

    return _lastNode;
}

Node *Graph::getNode(const size_t id) const
{
    return (_nodes.at(id) != nullptr) ? _nodes.at(id).get() : nullptr;
}

size_t Graph::getLatestNode() const
{
    return _lastNode;
}

void Graph::removeNode(const size_t id)
{
    _nodes.erase(id);
}

const std::vector<std::unique_ptr<Edge>>& Graph::getEdges() const
{
    return _edges;
}

const Graph::NodeMap &Graph::getNodes() const
{
    return _nodes;
}

QString Graph::toJSON() const
{
    QJsonArray arr;

    for (const auto& node: _nodes)
    {
        arr.append(node.second->toJSON());
    }

    QJsonDocument doc(arr);

    return QString(doc.toJson(QJsonDocument::Compact));
}
