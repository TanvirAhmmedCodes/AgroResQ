#include "CropService.h"
#include "../core/AuthManager.h"

namespace AgroResQ
{
namespace Services
{

CropService::CropService() = default;

bool CropService::addCrop(
    const std::string& cropName,
    const std::string& season,
    const std::string& suitableSoil,
    double waterRequirement)
{
    if (cropName.empty())
        return false;

    if (season.empty())
        return false;

    if (suitableSoil.empty())
        return false;

    if (waterRequirement < 0)
        return false;

    int id = idGenerator.generateNextId("database/crops.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Crop crop(
        id,
        cropName,
        season,
        suitableSoil,
        waterRequirement,
        tenantId);

    return cropRepository.add(crop);
}

bool CropService::updateCrop(
    int id,
    const std::string& cropName,
    const std::string& season,
    const std::string& suitableSoil,
    double waterRequirement)
{
    if (cropName.empty())
        return false;

    if (season.empty())
        return false;

    if (suitableSoil.empty())
        return false;

    if (waterRequirement < 0)
        return false;

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Crop crop(
        id,
        cropName,
        season,
        suitableSoil,
        waterRequirement,
        tenantId);

    return cropRepository.update(crop);
}

bool CropService::deleteCrop(int id)
{
    return cropRepository.remove(id);
}

bool CropService::searchCrop(
    int id,
    Entities::Crop& crop)
{
    return cropRepository.getById(id, crop);
}

std::vector<Entities::Crop> CropService::getAllCrops()
{
    return cropRepository.getAll();
}

}
}