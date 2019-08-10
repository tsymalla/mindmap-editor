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

    using NodeMap = std::unordered_map<size_t, std::unique_ptr<Node>>;
    NodeMap _nodes;
    std::vector<std::unique_ptr<Edge>> _edges;

public:
    Graph();
    Graph(const Graph& rhs) = default;
    Graph(Graph&& rhs) = default;

    virtual ~Graph();

    void connectNodes(size_t from, size_t to);
    size_t addNode();
    size_t addNode(const std::string& content);
    Node* getNode(const size_t id) const;
    size_t getLatestNode() const;
    void removeNode(const size_t id);

    const std::vector<std::unique_ptr<Edge>>& getEdges() const;
    const NodeMap& getNodes() const;

    size_t getNodeCount() const;

    QString toJSON() const;
};

#endif // GRAPH_HPP
