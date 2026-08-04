#pragma once

#include <vector>
#include <string>

#include "../entities/Shelter.h"
#include "../repositories/disaster/ShelterRepository.h"
#include "../core/IDGenerator.h"
#include "../core/Validator.h"

namespace AgroResQ
{
namespace Services
{

class ShelterService
{
private:
    Repositories::ShelterRepository shelterRepository;
    Core::Validator validator;
    Core::IDGenerator idGenerator;

public:
    ShelterService();

    bool addShelter(
        const std::string& name,
        const std::string& location,
        int capacity,
        int occupied);

    bool updateShelter(
        int id,
        const std::string& name,
        const std::string& location,
        int capacity,
        int occupied);

    bool deleteShelter(
        int id);

    bool searchShelter(
        int id,
        Entities::Shelter& shelter);

    std::vector<Entities::Shelter> getAllShelters();

    std::vector<Entities::Shelter> getAvailableShelters();
};

}
}