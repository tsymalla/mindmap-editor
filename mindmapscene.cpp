#include "mindmapscene.hpp"

#include <QJsonArray>
#include <QJsonDocument>
#include <mutex>
#include <QDebug>
#include <QKeyEvent>
#include <QJsonObject>

MindmapScene::MindmapScene(QObject* parent): QGraphicsScene (parent), _selectedNode(nullptr)
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

void MindmapScene::reset()
{
    _selectedNode = nullptr;

    _mindmap.clear();
    update();
}

void MindmapScene::nodePositionChanged(MindmapNode* node)
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

void MindmapScene::selectionChanged(MindmapNode* node)
{
    /*if (_selectedNode != nullptr)
    {
        _selectedNode->setBrush(_brush);
    }

    _selectedNode = node;
    _selectedNode->setBrush(QBrush(Qt::blue));*/
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
    //node->resize();
    update();
}

void MindmapScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key::Key_Tab)
    {
        //addNode();

        emit notifyMindmapChanged(false);
    }
    else if (event->key() == Qt::Key::Key_F2)
    {
        emit passNodeDoubleClick(_selectedNode);
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

    /*if (!_nodes.empty())
    {
        auto firstNode = _mindMap._nodes.begin()->second.get();
        _selectedNode = firstNode;
        selectionChanged(firstNode);
    }
    else
    {
        _selectedNode = nullptr;
    }*/

    update();

    emit notifyMindmapChanged(false);
}
