#include "Node.hpp"
#include <iostream>
#include <assert.h>

Node::Node(const std::string& name): _parentNode(nullptr), _name(name)
{
}

Node::Node(Node* parentNode, const std::string & name): _parentNode(parentNode), _name(name)
{
}

Node::~Node()
{
    _siblings.clear();
}

Node* Node::addSibling(const std::string& name)
{
    auto sibling = std::make_unique<Node>(this, name);
    _siblings.emplace_back(std::move(sibling));

    return getSiblingByName(name);
}

void Node::setParent(Node* const parent)
{
    assert(parent != nullptr);

    _parentNode = parent;
}

void Node::setName(const std::string& name)
{
    assert(!name.empty());
    _name = name;
}

void Node::setContent(const std::string& content)
{
    _content = content;
}

std::vector<std::unique_ptr<Node>> const& Node::getSiblings() const
{
    return _siblings;
}

std::string Node::getName() const
{
    return _name;
}

std::string Node::getContent() const
{
    return _content;
}

Node* Node::getSiblingByName(const std::string& name) const
{
    for (const auto& sibling : _siblings)
    {
        if (sibling->getName() == name)
        {
            return sibling.get();
        }
    }

    return nullptr;
}

bool Node::hasSiblings() const
{
    return (_siblings.size() > 0);
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

std::ostream& Node::printTree(std::ostream& os, Node* parent, int& indent)
{
#define ADD_INDENT for (auto i = 0; i < indent; ++i) { os << "\t"; }
#define ECHO_Node(x) os << x->getName() << " - " << x->getContent();
    if (parent == nullptr)
    {
        ++indent;
        ADD_INDENT;
        ECHO_Node(this);
    }
    os << std::endl;

    for (const auto& sibling : _siblings)
    {
        ++indent;

        ADD_INDENT;
        ECHO_Node(sibling);

        if (sibling->hasSiblings())
        {
            os << std::endl;
            sibling->printTree(os, this, ++indent);
        }

        os << std::endl;

        --indent;
    }

    --indent;

    return os;
}
