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

    std::string _content;
    Meta _metaData;

public:
    Node(const std::string& content);

    virtual ~Node();

    void setContent(const std::string& content);
    std::string getContent() const;

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    auto getX() const;
    auto getY() const;
    auto getWidth() const;
    auto getHeight() const;
};

#endif // Node_HPP
