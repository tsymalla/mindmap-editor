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

    const size_t _id;
    std::string _content;
    Meta _metaData;

public:
    Node(size_t id, const std::string& content);

    virtual ~Node();

    size_t getId() const;

    void setContent(const std::string& content);
    std::string getContent() const;

    void setX(double x);
    void setY(double y);
    void setWidth(double width);
    void setHeight(double height);

    double getX() const;
    double getY() const;
    double getWidth() const;
    double getHeight() const;
};

#endif // Node_HPP
