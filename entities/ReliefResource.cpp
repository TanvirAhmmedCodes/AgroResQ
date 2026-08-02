#include "ReliefResource.h"

#include <sstream>

namespace AgroResQ
{
namespace Entities
{

ReliefResource::ReliefResource()
    : quantity(0)
{
}

ReliefResource::ReliefResource(
    int id,
    const std::string& resourceName,
    const std::string& category,
    int quantity,
    const std::string& unit)
{
    setId(id);

    this->resourceName = resourceName;
    this->category = category;
    this->quantity = quantity;
    this->unit = unit;
}

void ReliefResource::setResourceName(
    const std::string& resourceName)
{
    this->resourceName = resourceName;
}

void ReliefResource::setCategory(
    const std::string& category)
{
    this->category = category;
}

void ReliefResource::setQuantity(
    int quantity)
{
    this->quantity = quantity;
}

void ReliefResource::setUnit(
    const std::string& unit)
{
    this->unit = unit;
}

std::string ReliefResource::getName() const
{
    return resourceName;
}

std::string ReliefResource::getCategory() const
{
    return category;
}

int ReliefResource::getQuantity() const
{
    return quantity;
}

std::string ReliefResource::getUnit() const
{
    return unit;
}

std::string ReliefResource::toString() const
{
    std::stringstream stream;

    stream
        << getId()
        << ","
        << resourceName
        << ","
        << category
        << ","
        << quantity
        << ","
        << unit;

    return stream.str();
}

}
}