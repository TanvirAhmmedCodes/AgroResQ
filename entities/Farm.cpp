#include "Farm.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Farm::Farm() : landArea(0.0) {}

        Farm::Farm(int id, const std::string& farmerName, const std::string& location,
                   double landArea, const std::string& soilType, const std::string& cropName,
                   const std::string& tenantId)
        {
            setId(id);
            this->farmerName = farmerName;
            this->location = location;
            this->landArea = landArea;
            this->soilType = soilType;
            this->cropName = cropName;
            this->tenantId = tenantId;
        }

        void Farm::setFarmerName(const std::string& farmerName) { this->farmerName = farmerName; }
        void Farm::setLocation(const std::string& location) { this->location = location; }
        void Farm::setLandArea(double landArea) { this->landArea = landArea; }
        void Farm::setSoilType(const std::string& soilType) { this->soilType = soilType; }
        void Farm::setCropName(const std::string& cropName) { this->cropName = cropName; }
        void Farm::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Farm::getFarmerName() const { return farmerName; }
        std::string Farm::getLocation() const { return location; }
        double Farm::getLandArea() const { return landArea; }
        std::string Farm::getSoilType() const { return soilType; }
        std::string Farm::getCropName() const { return cropName; }
        std::string Farm::getTenantId() const { return tenantId; }

        std::string Farm::toString() const
        {
            std::stringstream ss;
            ss << getId() << "," << farmerName << "," << location << ","
               << landArea << "," << soilType << "," << cropName << ","
               << tenantId;
            return ss.str();
        }
    }
}