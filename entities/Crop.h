#pragma once

#include <string>

#include "../core/BaseEntity.h"

namespace AgroResQ
{
namespace Entities
{

class Crop : public Core::BaseEntity
{
private:
    std::string cropName;
    std::string season;
    std::string suitableSoil;
    double waterRequirement;

public:
    Crop();

    Crop(
        int id,
        const std::string& cropName,
        const std::string& season,
        const std::string& suitableSoil,
        double waterRequirement);

    void setCropName(const std::string& cropName);
    void setSeason(const std::string& season);
    void setSuitableSoil(const std::string& suitableSoil);
    void setWaterRequirement(double waterRequirement);

    std::string getCropName() const;
    std::string getSeason() const;
    std::string getSuitableSoil() const;
    double getWaterRequirement() const;

    std::string toString() const;
};

}
}