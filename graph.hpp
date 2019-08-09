#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <memory>
#include "node.hpp"
#include "edge.hpp"

class Graph
{
private:
    size_t _lastNode;
    std::unordered_map<size_t, std::unique_ptr<Node>> _nodes;
    std::vector<std::unique_ptr<Edge>> _edges;

public:
    Graph();
    Graph(const Graph& rhs) = default;
    Graph(Graph&& rhs) = default;

    virtual ~Graph();

    void connectNodes(size_t from, size_t to);
    size_t addNode(const std::string& content);
    Node* getNode(const size_t id) const;
};

#endif // GRAPH_HPP
