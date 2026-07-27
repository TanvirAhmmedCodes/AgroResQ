#pragma once

#include <vector>

#include "../core/IDGenerator.h"
#include "../core/Validator.h"

#include "../entities/Soil.h"

#include "../repositories/agriculture/SoilRepository.h"

namespace AgroResQ
{
namespace Services
{

class SoilService
{
private:
    Repositories::SoilRepository soilRepository;

    Core::Validator validator;
    Core::IDGenerator idGenerator;

public:
    SoilService();

    bool addSoil(
        const std::string& farmId,
        double phLevel,
        double moisture,
        const std::string& soilType);

    bool updateSoil(
        int id,
        const std::string& farmId,
        double phLevel,
        double moisture,
        const std::string& soilType);

    bool deleteSoil(int id);

    bool searchSoil(
        int id,
        Entities::Soil& soil);

    std::vector<Entities::Soil> getAllSoils();
};

}
}