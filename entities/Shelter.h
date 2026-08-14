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
            std::string tenantId;

        public:
            Shelter();
            Shelter(int id, const std::string& name, const std::string& location,
                    int capacity, int occupied, const std::string& tenantId = "");

            void setName(const std::string& name);
            void setLocation(const std::string& location);
            void setCapacity(int capacity);
            void setOccupied(int occupied);
            void setTenantId(const std::string& tenantId);

            std::string getName() const;
            std::string getLocation() const;
            int getCapacity() const;
            int getOccupied() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}