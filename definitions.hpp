#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#include <vector>
#include <cstdint>
#include <QHash>

class MindmapNode;
class MindmapEdge;

using NodeId = int;
using NodeRawPtr = MindmapNode*;
using EdgeRawPtr = MindmapEdge*;
using NodeList = std::vector<NodeRawPtr>;
using EdgeList = std::vector<EdgeRawPtr>;

// Use QString as key in unordered_map containers
namespace std
{
    template<> struct hash<QString>
    {
        std::size_t operator()(const QString& str) const noexcept
        {
            return qHash(str);
        }
    };
}

#endif // DEFINITIONS_HPP
