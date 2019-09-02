#ifndef JSONSERIALIZABLE_HPP
#define JSONSERIALIZABLE_HPP

#include <QJsonValue>
#include <QString>

class JSONSerializable
{
public:
    virtual QJsonValue toJSON() const = 0;
    virtual void fromJSON(const QJsonValue &json) = 0;

    virtual ~JSONSerializable() {}
};

#endif // JSONSERIALIZABLE_HPP
