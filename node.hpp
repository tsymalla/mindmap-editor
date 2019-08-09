#ifndef Node_HPP
#define Node_HPP

#include <vector>
#include <memory>
#include <string>

class Node
{
private:
    struct Meta
    {
        double x;
        double y;
        double width;
        double height;
    };

    Node* _parentNode;
    std::vector<std::unique_ptr<Node>> _siblings;
    std::string _name;
    std::string _content;
    Meta _metaData;

public:
    Node(const std::string& name);
    Node(Node* parentNode, const std::string& name);

    virtual ~Node();

    Node* addSibling(const std::string& name);
    void setParent(Node* const parent);
    void setName(const std::string& name);
    void setContent(const std::string& content);

    std::vector<std::unique_ptr<Node>> const& getSiblings() const;
    std::string getName() const;
    std::string getContent() const;
    Node* getSiblingByName(const std::string& name) const;
    bool hasSiblings() const;

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    auto getX() const;
    auto getY() const;
    auto getWidth() const;
    auto getHeight() const;

    std::ostream& printTree(std::ostream& os, Node* parent, int& indent);
};

#endif // Node_HPP
