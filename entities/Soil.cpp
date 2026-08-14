#include "Soil.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Soil::Soil() : phLevel(0.0), moisture(0.0) {}

        Soil::Soil(int id, const std::string& farmId, double phLevel, double moisture,
                   const std::string& soilType, const std::string& tenantId)
        {
            setId(id);
            this->farmId = farmId;
            this->phLevel = phLevel;
            this->moisture = moisture;
            this->soilType = soilType;
            this->tenantId = tenantId;
        }

        void Soil::setFarmId(const std::string& farmId) { this->farmId = farmId; }
        void Soil::setPhLevel(double phLevel) { this->phLevel = phLevel; }
        void Soil::setMoisture(double moisture) { this->moisture = moisture; }
        void Soil::setSoilType(const std::string& soilType) { this->soilType = soilType; }
        void Soil::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Soil::getFarmId() const { return farmId; }
        double Soil::getPhLevel() const { return phLevel; }
        double Soil::getMoisture() const { return moisture; }
        std::string Soil::getSoilType() const { return soilType; }
        std::string Soil::getTenantId() const { return tenantId; }

        std::string Soil::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << farmId << "," << phLevel << ","
                   << moisture << "," << soilType << "," << tenantId;
            return stream.str();
        }
    }
}