#pragma once

#include <vector>

#include "../core/IDGenerator.h"

#include "../entities/Crop.h"

#include "../repositories/agriculture/CropRepository.h"

namespace AgroResQ
{
namespace Services
{

class CropService
{
private:
    Repositories::CropRepository cropRepository;

    Core::IDGenerator idGenerator;

public:
    CropService();

    bool addCrop(
        const std::string& cropName,
        const std::string& season,
        const std::string& suitableSoil,
        double waterRequirement);

    bool updateCrop(
        int id,
        const std::string& cropName,
        const std::string& season,
        const std::string& suitableSoil,
        double waterRequirement);

    bool deleteCrop(int id);

    bool searchCrop(
        int id,
        Entities::Crop& crop);

    std::vector<Entities::Crop> getAllCrops();
};

}
}