#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Soil : public Core::BaseEntity
        {
        private:
            std::string farmId;
            double phLevel;
            double moisture;
            std::string soilType;
            std::string tenantId;

        public:
            Soil();
            Soil(int id, const std::string& farmId, double phLevel, double moisture,
                 const std::string& soilType, const std::string& tenantId = "");

            void setFarmId(const std::string& farmId);
            void setPhLevel(double phLevel);
            void setMoisture(double moisture);
            void setSoilType(const std::string& soilType);
            void setTenantId(const std::string& tenantId);

            std::string getFarmId() const;
            double getPhLevel() const;
            double getMoisture() const;
            std::string getSoilType() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}