#include "ShelterService.h"
#include "../core/AuthManager.h"

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

    int id = idGenerator.generateNextId("database/shelters.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Shelter shelter(
        id,
        name,
        location,
        capacity,
        occupied,
        tenantId);

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

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::Shelter shelter(
        id,
        name,
        location,
        capacity,
        occupied,
        tenantId);

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
    return shelterRepository.getById(id, shelter);
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

    auto shelters = shelterRepository.getAll();

    for(auto& shelter : shelters)
    {
        if(shelter.getOccupied() < shelter.getCapacity())
        {
            available.push_back(shelter);
        }
    }

    return available;
}

}
}