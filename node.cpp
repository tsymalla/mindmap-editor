#include "Node.hpp"
#include <iostream>
#include <assert.h>

Node::Node(const std::string& content):  _content(content)
{
}

Node::~Node()
{
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

auto Node::getX() const
{
    return _metaData.x;
}

auto Node::getY() const
{
    return _metaData.y;
}

auto Node::getWidth() const
{
    return _metaData.width;
}

auto Node::getHeight() const
{
    return _metaData.height;
}
