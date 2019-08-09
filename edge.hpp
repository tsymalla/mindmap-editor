#ifndef EDGE_HPP
#define EDGE_HPP

#include "node.hpp"

class Edge
{
private:
    size_t _from;
    size_t _to;
    std::string _label;

public:
    Edge(size_t from, size_t to, const std::string& label);

    size_t getFrom() const;
    size_t getTo() const;
};

#endif // EDGE_HPP
