#pragma once

#include <vector>

#include "../core/IDGenerator.h"

#include "../entities/ReliefResource.h"

#include "../repositories/disaster/ReliefRepository.h"

namespace AgroResQ
{
namespace Services
{

class ReliefService
{
private:

    Repositories::ReliefRepository reliefRepository;

    Core::IDGenerator idGenerator;

public:

    ReliefService();

    bool addReliefResource(
        const std::string& name,
        const std::string& category,
        int quantity,
        const std::string& unit);

    bool updateReliefResource(
        int id,
        const std::string& name,
        const std::string& category,
        int quantity,
        const std::string& unit);

    bool deleteReliefResource(
        int id);

    bool searchReliefResource(
        int id,
        Entities::ReliefResource& resource);

    std::vector<Entities::ReliefResource> getAllReliefResources();
};

}
}