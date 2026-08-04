#pragma once

#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
namespace Entities
{

class Shelter : public Core::BaseEntity
{
private:
    std::string name;
    std::string location;
    int capacity;
    int occupied;

public:
    Shelter();

    Shelter(
        int id,
        const std::string& name,
        const std::string& location,
        int capacity,
        int occupied);

    void setName(const std::string& name);
    void setLocation(const std::string& location);
    void setCapacity(int capacity);
    void setOccupied(int occupied);

    std::string getName() const;
    std::string getLocation() const;
    int getCapacity() const;
    int getOccupied() const;

    std::string toString() const;
};

}
}