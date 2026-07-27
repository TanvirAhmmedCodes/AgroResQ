#pragma once

#include <string>
#include <vector>

#include "../core/IDGenerator.h"
#include "../core/Validator.h"
#include "../entities/Farm.h"
#include "../repositories/agriculture/FarmRepository.h"

namespace AgroResQ
{
namespace Services
{

class AgricultureService
{
private:
    Repositories::FarmRepository farmRepository;
    Core::Validator validator;
    Core::IDGenerator idGenerator;

public:
    AgricultureService();

    bool addFarm(
        const std::string& farmerName,
        const std::string& location,
        double landArea,
        const std::string& soilType,
        const std::string& cropName);

    bool updateFarm(
        int id,
        const std::string& farmerName,
        const std::string& location,
        double landArea,
        const std::string& soilType,
        const std::string& cropName);

    bool deleteFarm(int id);

    bool searchFarm(
        int id,
        Entities::Farm& farm);

    std::vector<Entities::Farm> getAllFarms();
};

}
}