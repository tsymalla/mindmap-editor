#include "graph.hpp"

Graph::Graph()
{
}

Graph::Graph(const std::vector<std::unique_ptr<Vertex>> rootVertices)
{
}

Graph::~Graph()
{
    _rootVertices.clear();
}

void Graph::addRootVertex(const std::string& name)
{
    auto root = std::make_unique<Vertex>(name);
    _rootVertices.emplace_back(std::move(root));
}

Vertex* Graph::getRootVertexByName(const std::string& name) const
{
    for (const auto& root : _rootVertices)
    {
        if (root->getName() == name)
        {
            return root.get();
        }
    }

    return nullptr;
}
