#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <memory>
#include "node.hpp"
#include "edge.hpp"

class Graph
{
private:
    std::unordered_map<size_t, std::unique_ptr<Node>> _vertices;
    std::vector<std::unique_ptr<Edge>> _edges;

public:
    Graph();
    Graph(const Graph& rhs) = default;
    Graph(Graph&& rhs) = default;

    virtual ~Graph();
};

#endif // GRAPH_HPP
