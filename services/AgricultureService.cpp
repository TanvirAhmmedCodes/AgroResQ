#include "AgricultureService.h"
#include "../core/AuthManager.h"

namespace AgroResQ
{
namespace Services
{

AgricultureService::AgricultureService() = default;

bool AgricultureService::addFarm(
    const std::string& farmerName,
    const std::string& location,
    double landArea,
    const std::string& soilType,
    const std::string& cropName)
{
    if (!validator.isValidName(farmerName))
        return false;

    if (!validator.isValidLocation(location))
        return false;

    if (landArea <= 0)
        return false;

    if (!validator.isValidName(soilType))
        return false;

    if (!validator.isValidName(cropName))
        return false;

    int id = idGenerator.generateNextId("database/farms.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Farm farm(
        id,
        farmerName,
        location,
        landArea,
        soilType,
        cropName,
        tenantId);

    return farmRepository.add(farm);
}

bool AgricultureService::updateFarm(
    int id,
    const std::string& farmerName,
    const std::string& location,
    double landArea,
    const std::string& soilType,
    const std::string& cropName)
{
    if (!validator.isValidName(farmerName))
        return false;

    if (!validator.isValidLocation(location))
        return false;

    if (landArea <= 0)
        return false;

    if (!validator.isValidName(soilType))
        return false;

    if (!validator.isValidName(cropName))
        return false;

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Farm farm(
        id,
        farmerName,
        location,
        landArea,
        soilType,
        cropName,
        tenantId);

    return farmRepository.update(farm);
}

bool AgricultureService::deleteFarm(int id)
{
    return farmRepository.remove(id);
}

bool AgricultureService::searchFarm(
    int id,
    Entities::Farm& farm)
{
    return farmRepository.getById(id, farm);
}

std::vector<Entities::Farm> AgricultureService::getAllFarms()
{
    return farmRepository.getAll();
}

}
}