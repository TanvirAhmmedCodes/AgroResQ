#pragma once

#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
namespace Entities
{

class ReliefResource : public Core::BaseEntity
{
private:

    std::string resourceName;

    std::string category;

    int quantity;

    std::string unit;

public:

    ReliefResource();

    ReliefResource(
        int id,
        const std::string& resourceName,
        const std::string& category,
        int quantity,
        const std::string& unit);

    void setResourceName(
        const std::string& resourceName);

    void setCategory(
        const std::string& category);

    void setQuantity(
        int quantity);

    void setUnit(
        const std::string& unit);

    std::string getName() const;

    std::string getCategory() const;

    int getQuantity() const;

    std::string getUnit() const;

    std::string toString() const;
};

}
}