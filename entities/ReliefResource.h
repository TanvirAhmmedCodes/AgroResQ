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
            std::string tenantId;

        public:
            ReliefResource();
            ReliefResource(int id, const std::string& resourceName, const std::string& category,
                           int quantity, const std::string& unit, const std::string& tenantId = "");

            void setResourceName(const std::string& resourceName);
            void setCategory(const std::string& category);
            void setQuantity(int quantity);
            void setUnit(const std::string& unit);
            void setTenantId(const std::string& tenantId);

            std::string getName() const;
            std::string getCategory() const;
            int getQuantity() const;
            std::string getUnit() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}