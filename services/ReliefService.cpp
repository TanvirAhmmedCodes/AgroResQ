#include "ReliefService.h"
#include "../core/AuthManager.h"

namespace AgroResQ
{
namespace Services
{

ReliefService::ReliefService() = default;

bool ReliefService::addReliefResource(
    const std::string& name,
    const std::string& category,
    int quantity,
    const std::string& unit)
{
    if(name.empty())
        return false;

    if(quantity < 0)
        return false;

    int id = idGenerator.generateNextId("database/relief.txt");
    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::ReliefResource resource(
        id,
        name,
        category,
        quantity,
        unit,
        tenantId);

    return reliefRepository.add(resource);
}

bool ReliefService::updateReliefResource(
    int id,
    const std::string& name,
    const std::string& category,
    int quantity,
    const std::string& unit)
{
    if(name.empty())
        return false;

    if(quantity < 0)
        return false;

    std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

    Entities::ReliefResource resource(
        id,
        name,
        category,
        quantity,
        unit,
        tenantId);

    return reliefRepository.update(resource);
}

bool ReliefService::deleteReliefResource(
    int id)
{
    return reliefRepository.remove(id);
}

bool ReliefService::searchReliefResource(
    int id,
    Entities::ReliefResource& resource)
{
    return reliefRepository.getById(id, resource);
}

std::vector<Entities::ReliefResource>
ReliefService::getAllReliefResources()
{
    return reliefRepository.getAll();
}

}
}