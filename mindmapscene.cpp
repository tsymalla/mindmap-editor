#include "mindmapnodegraphicsitem.hpp"
#include "mindmapscene.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <mutex>
#include <QDebug>
#include <QKeyEvent>
#include <QJsonObject>

MindmapScene::MindmapScene(QObject* parent): QGraphicsScene (parent), _selectedNode(nullptr), _selectedGraphicsNode(nullptr)
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

    /*for (const auto& node: _nodes)
    {
        arr.append(node.second->toJSON());
    }*/

    QJsonDocument doc(arr);

    return QString(doc.toJson(QJsonDocument::Compact));
}

void MindmapScene::fromJSON(const QString &json)
{
    //clear();

    QJsonDocument obj = QJsonDocument::fromJson(json.toUtf8());

    /*for (const auto node: obj.array())
    {
        auto newNode = addNode();
        newNode->fromJSON(node.toObject());
    }

    for (const auto& node: _nodes)
    {
        node.second->resize();
        nodePositionChanged(node.second.get());
    }*/
}

void MindmapScene::_focusSelection(MindmapNodeGraphicsItem* item)
{
    if (item == _selectedGraphicsNode)
    {
        return;
    }

    if (_selectedGraphicsNode != nullptr)
    {
        _selectedGraphicsNode->setBrush(_brush);
        _selectedGraphicsNode->setPen(_pen);
    }

    setFocusItem(item);

    _selectedGraphicsNode = item;
    _selectedGraphicsNode->setBrush(QBrush(Qt::blue));
}

void MindmapScene::addNode()
{
    addNode("");
}

void MindmapScene::addNode(const QString& nodeName)
{
    _selectedNode = _mindmap.addNode(nodeName, _selectedNode);
    auto graphicsNode = new MindmapNodeGraphicsItem(_selectedNode);

    graphicsNode->setBrush(_brush);
    graphicsNode->setPen(_pen);

    connect(graphicsNode, &MindmapNodeGraphicsItem::selected, this, &MindmapScene::nodeSelectionChanged);
    connect(graphicsNode, &MindmapNodeGraphicsItem::positionChanged, this, &MindmapScene::nodePositionChanged);
    connect(graphicsNode, &MindmapNodeGraphicsItem::doubleClicked, this, &MindmapScene::nodeDoubleClicked);

    this->addItem(graphicsNode);
    _focusSelection(graphicsNode);
}

void MindmapScene::reset()
{
    _selectedNode = nullptr;

    _mindmap.clear();
    clear();

    update();
    addNode("Mindmap");

    emit notifyMindmapChanged(true);
}

void MindmapScene::nodePositionChanged(MindmapNodeGraphicsItem* item, NodeRawPtr node)
{
    /*for (const auto& it: _nodeConnectors)
    {
        MindmapEdge* edge = it.second.get();
        if (edge->isFrom(node) || edge->isTo(node))
        {
            // update node connection points
            edge->redraw();
        }
    }*/

    update();

    emit notifyMindmapChanged(false);
}

void MindmapScene::nodeSelectionChanged(MindmapNodeGraphicsItem* item, NodeRawPtr node)
{
    _selectedNode = node;
    _focusSelection(item);
}

void MindmapScene::nodeDoubleClicked(MindmapNodeGraphicsItem* item, NodeRawPtr node)
{
    // pass-through signal to main window
    emit passNodeDoubleClick(item, node);
}

void MindmapScene::changeNodeContent(MindmapNodeGraphicsItem* item, const QString& content)
{
    item->changeNodeContent(content);
    update();
    //node->resize();
    //update();
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
        auto focussedNode = dynamic_cast<MindmapNodeGraphicsItem*>(focusItem());
        emit passNodeDoubleClick(focussedNode, _selectedNode);
    }
}

/*void MindmapScene::_addEdge(MindmapNode* from, MindmapNode* to)
{
    addItem(ptr);
}*/

void MindmapScene::removeSelectedNodes()
{
    if (_selectedNode == nullptr)
    {
        return;
    }

    auto ret = _mindmap.removeNode(_selectedNode);
    if (ret)
    {
        removeItem(_selectedGraphicsNode);
        _selectedGraphicsNode = nullptr;

        if (getNodeCount() == 0)
        {
            update();
            return;
        }

        _selectedNode = _mindmap.getLastNode();
    }

    update();

    emit notifyMindmapChanged(false);
}

int MindmapScene::getNodeCount() const
{
    return _mindmap.getNodeCount();
}
