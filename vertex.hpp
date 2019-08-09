#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <vector>
#include <memory>
#include <string>

class Vertex
{
private:
    struct Meta
    {
        double x;
        double y;
        double width;
        double height;
    };

    Vertex* _parentVertex;
    std::vector<std::unique_ptr<Vertex>> _siblings;
    std::string _name;
    std::string _content;
    Meta _metaData;

public:
    Vertex(const std::string& name);
    Vertex(Vertex* parentVertex, const std::string& name);

    virtual ~Vertex();

    Vertex* addSibling(const std::string& name);
    void setParent(Vertex* const parent);
    void setName(const std::string& name);
    void setContent(const std::string& content);

    std::vector<std::unique_ptr<Vertex>> const& getSiblings() const;
    std::string getName() const;
    std::string getContent() const;
    Vertex* getSiblingByName(const std::string& name) const;
    bool hasSiblings() const;

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    auto getX() const;
    auto getY() const;
    auto getWidth() const;
    auto getHeight() const;

    std::ostream& printTree(std::ostream& os, Vertex* parent, int& indent);
};

#endif // VERTEX_HPP
