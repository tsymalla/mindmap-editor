#include "mindmapscene.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <mutex>
#include <QDebug>
#include <QKeyEvent>
#include <QJsonObject>

MindmapScene::MindmapScene(QObject* parent): QGraphicsScene (parent), _lastNodeId(0), _selectedNode(nullptr)
{
    _backgroundBrush.setColor(Qt::white);

    _brush.setColor(Qt::green);
    _brush.setStyle(Qt::BrushStyle::SolidPattern);

    _pen.setColor(Qt::black);
    _font.setFamily("Arial");
    _font.setWeight(20);

    setBackgroundBrush(_backgroundBrush);
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
    //clear();

    QJsonDocument obj = QJsonDocument::fromJson(json.toUtf8());

    for (const auto node: obj.array())
    {
        auto newNode = addNode();
        newNode->fromJSON(node.toObject());
    }

    for (const auto& node: _nodes)
    {
        node.second->resize();
        nodePositionChanged(node.second.get());
    }
}

MindmapNode *MindmapScene::addNode()
{
    return addNode("");
}

MindmapNode *MindmapScene::addNode(const QString& content)
{
    std::mutex m;
    std::lock_guard<std::mutex> guard(m);

    ++_lastNodeId;

    auto actualContent = content;
    if (content.isEmpty())
    {
        actualContent = "Node " + QString::number(_lastNodeId);
    }

    auto node = std::make_unique<MindmapNode>(_lastNodeId, actualContent, _brush, _pen, _font);

    auto ptr = node.get();
    connect(ptr, &MindmapNode::nodeSelected, this, &MindmapScene::selectionChanged);
    connect(ptr, &MindmapNode::positionChanged, this, &MindmapScene::nodePositionChanged);
    connect(ptr, &MindmapNode::nodeDoubleClick, this, &MindmapScene::nodeDoubleClick);

    _nodes.insert(std::make_pair(_lastNodeId, std::move(node)));

    addItem(ptr);

    if (_selectedNode != nullptr)
    {
        _addEdge(_selectedNode, ptr);
    }

    selectionChanged(ptr);
    update();

    return ptr;
}

MindmapNode *MindmapScene::getNodeById(const size_t id) const
{
    return (_nodes.at(id)) ? _nodes.at(id).get() : nullptr;
}

int MindmapScene::getNodeCount() const
{
    return _nodes.size();
}

void MindmapScene::reset()
{
    _nodes.clear();
    _nodeConnectors.clear();

    _selectedNode = nullptr;
    _lastNodeId = 0;

    clear();
    update();
}

void MindmapScene::nodePositionChanged(MindmapNode* node)
{
    for (const auto& it: _nodeConnectors)
    {
        MindmapEdge* edge = it.second.get();
        if (edge->isFrom(node) || edge->isTo(node))
        {
            // update node connection points
            edge->redraw();
        }
    }

    update();

    emit notifyMindmapChanged(false);
}

void MindmapScene::selectionChanged(MindmapNode* node)
{
    if (_selectedNode != nullptr)
    {
        _selectedNode->setBrush(_brush);
    }

    _selectedNode = node;
    _selectedNode->setBrush(QBrush(Qt::blue));
}

void MindmapScene::nodeDoubleClick(MindmapNode *node)
{
    // pass-through signal to main window
    emit passNodeDoubleClick(node);
}

void MindmapScene::changeNodeContent(MindmapNode* node, const QString& content)
{
    node->setContent(content);
    update();
    node->resize();
    update();
}

void MindmapScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Tab)
    {
        addNode();

        emit notifyMindmapChanged(false);
    }
    else if (event->key() == Qt::Key::Key_F2)
    {
        emit passNodeDoubleClick(_selectedNode);
    }
}

std::string MindmapScene::_getEdgeId(size_t from, size_t to) const
{
    return std::to_string(from) + "_" + std::to_string(to);
}

void MindmapScene::_addEdge(MindmapNode* from, MindmapNode* to)
{
    if (from == nullptr || to == nullptr)
    {
        return;
    }

    auto newEdge = std::make_unique<MindmapEdge>(from, to, _pen);
    auto ptr = newEdge.get();

    _nodeConnectors.insert(std::make_pair(_getEdgeId(from->getNodeId(), to->getNodeId()), std::move(newEdge)));

    addItem(ptr);
}

void MindmapScene::removeSelectedNodes()
{
    if (_selectedNode == nullptr)
    {
        return;
    }

    std::vector<std::string> removables;
    for (const auto& connector: _nodeConnectors)
    {
        auto edge = connector.second.get();

        if (edge->isFrom(_selectedNode) || edge->isTo(_selectedNode))
        {
            removables.push_back(connector.first);
        }
    }

    for (const auto& removable: removables)
    {
        _nodeConnectors.erase(removable);
    }

    _nodes.erase(_selectedNode->getNodeId());

    if (!_nodes.empty())
    {
        auto firstNode = _nodes.begin()->second.get();
        _selectedNode = firstNode;
        selectionChanged(firstNode);
    }
    else
    {
        _selectedNode = nullptr;
    }

    update();

    emit notifyMindmapChanged(false);
}
