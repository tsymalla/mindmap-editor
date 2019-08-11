#include "mindmapscene.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <mutex>
#include <QDebug>

MindmapScene::MindmapScene(QObject* parent): QGraphicsScene (parent), _lastNodeId(0)
{
    _brush.setColor(Qt::green);
    _brush.setStyle(Qt::BrushStyle::SolidPattern);

    _pen.setColor(Qt::black);
    _font.setFamily("Arial");
    _font.setWeight(20);
}

QString MindmapScene::toJSON() const
{
    QJsonArray arr;

    for (const auto& node: _nodes)
    {
        arr.append(node.second->toJSON());
    }

    QJsonDocument doc(arr);

    return QString(doc.toJson(QJsonDocument::Compact));
}

void MindmapScene::fromJSON(const QString &json)
{
    clear();

}

MindmapNode *MindmapScene::addNode()
{
    return addNode("");
}

MindmapNode *MindmapScene::addNode(const std::string &content)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    ++_lastNodeId;

    auto actualContent = content;
    if (content.empty())
    {
        actualContent = "Node " + std::to_string(_lastNodeId);
    }

    auto node = std::make_unique<MindmapNode>(_lastNodeId, actualContent, _brush, _pen, _font);

    auto ptr = node.get();
    connect(ptr, &MindmapNode::nodeSelected, this, &MindmapScene::selectionChanged);

    _nodes.insert(std::make_pair(_lastNodeId, std::move(node)));

    addItem(ptr);

    return ptr;
}

MindmapNode *MindmapScene::getNodeById(const size_t id) const
{
    return (_nodes.at(id)) ? _nodes.at(id).get() : nullptr;
}

size_t MindmapScene::getNodeCount() const
{
    return _nodes.size();
}

void MindmapScene::reset()
{
    _nodes.clear();
    _nodeConnectors.clear();
    clear();
    update();
}

void MindmapScene::nodeAdded(MindmapNode *parent)
{
    auto newNode = addNode();
    _addEdge(parent, newNode);

    update();
}

void MindmapScene::nodePositionChanged(MindmapNode* node)
{
}

void MindmapScene::selectionChanged(MindmapNode* node)
{
    _selectedNode = node;
    _selectedNode->setBrush(QBrush(Qt::blue));
}

std::string MindmapScene::_getEdgeId(size_t from, size_t to) const
{
    return std::to_string(from) + "_" + std::to_string(to);
}

void MindmapScene::_addEdge(MindmapNode* from, MindmapNode* to)
{
    auto newEdge = std::make_unique<MindmapEdge>(from, to, _pen);
    auto ptr = newEdge.get();

    _nodeConnectors.insert(std::make_pair(_getEdgeId(from->getNodeId(), to->getNodeId()), std::move(newEdge)));

    addItem(ptr);
}
