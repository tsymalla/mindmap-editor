#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <memory>
#include "vertex.hpp"

class Graph
{
private:
    std::vector<std::unique_ptr<Vertex>> _rootVertices;

public:
    Graph();
    Graph(const std::vector<std::unique_ptr<Vertex>> rootVertices);
    Graph(const Graph& rhs) = default;
    Graph(Graph&& rhs) = default;

    virtual ~Graph();

    void addRootVertex(const std::string& name);
    Vertex* getRootVertexByName(const std::string& name) const;

    friend std::ostream& operator<<(std::ostream& os, const Graph& graph)
    {
        int indent = 0;

        for (const auto& root : graph._rootVertices)
        {
            os << root->getName();

            for (const auto& sibling : root->getSiblings())
            {
                os << std::endl;
                sibling->printTree(os, nullptr, indent);
            }

            os << std::endl;
        }

        return os;
    }
};

#endif // GRAPH_HPP
