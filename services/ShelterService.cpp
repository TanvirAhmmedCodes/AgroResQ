#include "ShelterService.h"

namespace AgroResQ
{
namespace Services
{

ShelterService::ShelterService() = default;

bool ShelterService::addShelter(
    const std::string& name,
    const std::string& location,
    int capacity,
    int occupied)
{
    if(name.empty())
        return false;

    if(location.empty())
        return false;

    if(capacity <= 0)
        return false;

    if(occupied < 0 || occupied > capacity)
        return false;

    int id =
        idGenerator.generateNextId(
            "database/shelters.txt");

    Entities::Shelter shelter(
        id,
        name,
        location,
        capacity,
        occupied);

    return shelterRepository.add(shelter);
}

bool ShelterService::updateShelter(
    int id,
    const std::string& name,
    const std::string& location,
    int capacity,
    int occupied)
{
    if(name.empty())
        return false;

    if(location.empty())
        return false;

    if(capacity <= 0)
        return false;

    if(occupied < 0 || occupied > capacity)
        return false;

    Entities::Shelter shelter(
        id,
        name,
        location,
        capacity,
        occupied);

    return shelterRepository.update(shelter);
}

bool ShelterService::deleteShelter(int id)
{
    return shelterRepository.remove(id);
}

bool ShelterService::searchShelter(
    int id,
    Entities::Shelter& shelter)
{
    return shelterRepository.getById(
        id,
        shelter);
}

std::vector<Entities::Shelter>
ShelterService::getAllShelters()
{
    return shelterRepository.getAll();
}

std::vector<Entities::Shelter>
ShelterService::getAvailableShelters()
{
    std::vector<Entities::Shelter> available;

    auto shelters =
        shelterRepository.getAll();

    for(auto& shelter : shelters)
    {
        if(shelter.getOccupied() <
           shelter.getCapacity())
        {
            available.push_back(
                shelter);
        }
    }

    return available;
}

}
}