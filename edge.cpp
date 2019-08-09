#include "edge.hpp"

Edge::Edge(size_t from, size_t to, const std::string& label): _from(from), _to(to), _label(label)
{

}

size_t Edge::getFrom() const
{
    return _from;
}

size_t Edge::getTo() const
{
    return _to;
}
