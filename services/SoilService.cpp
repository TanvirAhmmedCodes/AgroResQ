#include "SoilService.h"

namespace AgroResQ
{
namespace Services
{

SoilService::SoilService() = default;


bool SoilService::addSoil(
    const std::string& farmId,
    double phLevel,
    double moisture,
    const std::string& soilType)
{
    if (farmId.empty())
        return false;

    if (phLevel < 0 || phLevel > 14)
        return false;

    if (moisture < 0 || moisture > 100)
        return false;

    if (soilType.empty())
        return false;


    int id = idGenerator.generateNextId(
        "database/soil.txt");


    Entities::Soil soil(
        id,
        farmId,
        phLevel,
        moisture,
        soilType);


    return soilRepository.add(soil);
}


bool SoilService::updateSoil(
    int id,
    const std::string& farmId,
    double phLevel,
    double moisture,
    const std::string& soilType)
{
    if (farmId.empty())
        return false;

    if (phLevel < 0 || phLevel > 14)
        return false;

    if (moisture < 0 || moisture > 100)
        return false;

    if (soilType.empty())
        return false;


    Entities::Soil soil(
        id,
        farmId,
        phLevel,
        moisture,
        soilType);


    return soilRepository.update(soil);
}


bool SoilService::deleteSoil(int id)
{
    return soilRepository.remove(id);
}


bool SoilService::searchSoil(
    int id,
    Entities::Soil& soil)
{
    return soilRepository.getById(
        id,
        soil);
}


std::vector<Entities::Soil> SoilService::getAllSoils()
{
    return soilRepository.getAll();
}

}
}