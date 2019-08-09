#include "vertex.hpp"
#include <iostream>
#include <assert.h>

Vertex::Vertex(const std::string& name): _parentVertex(nullptr), _name(name)
{
}

Vertex::Vertex(Vertex* parentVertex, const std::string & name): _parentVertex(parentVertex), _name(name)
{
}

Vertex::~Vertex()
{
    _siblings.clear();
}

Vertex* Vertex::addSibling(const std::string& name)
{
    auto sibling = std::make_unique<Vertex>(this, name);
    _siblings.emplace_back(std::move(sibling));

    return getSiblingByName(name);
}

void Vertex::setParent(Vertex* const parent)
{
    assert(parent != nullptr);

    _parentVertex = parent;
}

void Vertex::setName(const std::string& name)
{
    assert(!name.empty());
    _name = name;
}

void Vertex::setContent(const std::string& content)
{
    _content = content;
}

std::vector<std::unique_ptr<Vertex>> const& Vertex::getSiblings() const
{
    return _siblings;
}

std::string Vertex::getName() const
{
    return _name;
}

std::string Vertex::getContent() const
{
    return _content;
}

Vertex* Vertex::getSiblingByName(const std::string& name) const
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

bool Vertex::hasSiblings() const
{
    return (_siblings.size() > 0);
}

void Vertex::setX(double x)
{
    _metaData.x = x;
}

void Vertex::setY(double y)
{
    _metaData.y = y;
}

void Vertex::setWidth(double width)
{
    _metaData.width = width;
}

void Vertex::setHeight(double height)
{
    _metaData.height = height;
}

auto Vertex::getX() const
{
    return _metaData.x;
}

auto Vertex::getY() const
{
    return _metaData.y;
}

auto Vertex::getWidth() const
{
    return _metaData.width;
}

auto Vertex::getHeight() const
{
    return _metaData.height;
}

std::ostream& Vertex::printTree(std::ostream& os, Vertex* parent, int& indent)
{
#define ADD_INDENT for (auto i = 0; i < indent; ++i) { os << "\t"; }
#define ECHO_VERTEX(x) os << x->getName() << " - " << x->getContent();
    if (parent == nullptr)
    {
        ++indent;
        ADD_INDENT;
        ECHO_VERTEX(this);
    }
    os << std::endl;

    for (const auto& sibling : _siblings)
    {
        ++indent;

        ADD_INDENT;
        ECHO_VERTEX(sibling);

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
