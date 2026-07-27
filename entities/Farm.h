#pragma once

#include <string>

#include "../core/BaseEntity.h"

namespace AgroResQ
{
namespace Entities
{

class Farm : public Core::BaseEntity
{
private:
    std::string farmerName;
    std::string location;
    double landArea;
    std::string soilType;
    std::string cropName;

public:
    Farm();

    Farm(
        int id,
        const std::string& farmerName,
        const std::string& location,
        double landArea,
        const std::string& soilType,
        const std::string& cropName);

    void setFarmerName(const std::string& farmerName);
    void setLocation(const std::string& location);
    void setLandArea(double landArea);
    void setSoilType(const std::string& soilType);
    void setCropName(const std::string& cropName);

    std::string getFarmerName() const;
    std::string getLocation() const;
    double getLandArea() const;
    std::string getSoilType() const;
    std::string getCropName() const;

    std::string toString() const;
};

}
}