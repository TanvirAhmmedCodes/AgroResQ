#include "ReliefResource.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        ReliefResource::ReliefResource() : quantity(0) {}

        ReliefResource::ReliefResource(int id, const std::string& resourceName, const std::string& category,
                                       int quantity, const std::string& unit, const std::string& tenantId)
        {
            setId(id);
            this->resourceName = resourceName;
            this->category = category;
            this->quantity = quantity;
            this->unit = unit;
            this->tenantId = tenantId;
        }

        void ReliefResource::setResourceName(const std::string& resourceName) { this->resourceName = resourceName; }
        void ReliefResource::setCategory(const std::string& category) { this->category = category; }
        void ReliefResource::setQuantity(int quantity) { this->quantity = quantity; }
        void ReliefResource::setUnit(const std::string& unit) { this->unit = unit; }
        void ReliefResource::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string ReliefResource::getName() const { return resourceName; }
        std::string ReliefResource::getCategory() const { return category; }
        int ReliefResource::getQuantity() const { return quantity; }
        std::string ReliefResource::getUnit() const { return unit; }
        std::string ReliefResource::getTenantId() const { return tenantId; }

        std::string ReliefResource::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << resourceName << "," << category << ","
                   << quantity << "," << unit << "," << tenantId;
            return stream.str();
        }
    }
}