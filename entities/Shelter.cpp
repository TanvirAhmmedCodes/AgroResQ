#include "Shelter.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Shelter::Shelter() : capacity(0), occupied(0) {}

        Shelter::Shelter(int id, const std::string& name, const std::string& location,
                         int capacity, int occupied, const std::string& tenantId)
        {
            setId(id);
            this->name = name;
            this->location = location;
            this->capacity = capacity;
            this->occupied = occupied;
            this->tenantId = tenantId;
        }

        void Shelter::setName(const std::string& name) { this->name = name; }
        void Shelter::setLocation(const std::string& location) { this->location = location; }
        void Shelter::setCapacity(int capacity) { this->capacity = capacity; }
        void Shelter::setOccupied(int occupied) { this->occupied = occupied; }
        void Shelter::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Shelter::getName() const { return name; }
        std::string Shelter::getLocation() const { return location; }
        int Shelter::getCapacity() const { return capacity; }
        int Shelter::getOccupied() const { return occupied; }
        std::string Shelter::getTenantId() const { return tenantId; }

        std::string Shelter::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << name << "," << location << ","
                   << capacity << "," << occupied << "," << tenantId;
            return stream.str();
        }
    }
}