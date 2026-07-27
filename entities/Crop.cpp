#include "Crop.h"

#include <sstream>

namespace AgroResQ
{
namespace Entities
{

Crop::Crop()
    : waterRequirement(0.0)
{
}

Crop::Crop(
    int id,
    const std::string& cropName,
    const std::string& season,
    const std::string& suitableSoil,
    double waterRequirement)
{
    setId(id);

    this->cropName = cropName;
    this->season = season;
    this->suitableSoil = suitableSoil;
    this->waterRequirement = waterRequirement;
}

void Crop::setCropName(const std::string& cropName)
{
    this->cropName = cropName;
}

void Crop::setSeason(const std::string& season)
{
    this->season = season;
}

void Crop::setSuitableSoil(const std::string& suitableSoil)
{
    this->suitableSoil = suitableSoil;
}

void Crop::setWaterRequirement(double waterRequirement)
{
    this->waterRequirement = waterRequirement;
}

std::string Crop::getCropName() const
{
    return cropName;
}

std::string Crop::getSeason() const
{
    return season;
}

std::string Crop::getSuitableSoil() const
{
    return suitableSoil;
}

double Crop::getWaterRequirement() const
{
    return waterRequirement;
}

std::string Crop::toString() const
{
    std::stringstream stream;

    stream << getId() << ","
           << cropName << ","
           << season << ","
           << suitableSoil << ","
           << waterRequirement;

    return stream.str();
}

}
}