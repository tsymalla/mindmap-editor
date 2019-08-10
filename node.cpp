#include "node.hpp"
#include <iostream>
#include <assert.h>
#include <QDebug>
#include <QJsonObject>

Node::Node(size_t id, const std::string& content):  _id(id), _content(content)
{
}

Node::~Node()
{
    qDebug() << "Destructing node";
}

size_t Node::getId() const
{
    return _id;
}

void Node::setContent(const std::string& content)
{
    _content = content;
}

std::string Node::getContent() const
{
    return _content;
}

void Node::setX(double x)
{
    _metaData.x = x;
}

void Node::setY(double y)
{
    _metaData.y = y;
}

void Node::setWidth(double width)
{
    _metaData.width = width;
}

void Node::setHeight(double height)
{
    _metaData.height = height;
}

double Node::getX() const
{
    return _metaData.x;
}

double Node::getY() const
{
    return _metaData.y;
}

double Node::getWidth() const
{
    return _metaData.width;
}

double Node::getHeight() const
{
    return _metaData.height;
}

QJsonValue Node::toJSON() const
{
    QJsonObject json;
    json["id"] = QVariant(static_cast<unsigned int>(_id)).toInt();
    json["content"] = QString::fromStdString(_content);
    json["x"] = QVariant(getX()).toReal();
    json["y"] = QVariant(getY()).toReal();
    json["w"] = QVariant(getWidth()).toReal();
    json["h"] = QVariant(getHeight()).toReal();

    return json;
}
