#include "ReliefRepository.h"

#include <fstream>
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

ReliefRepository::ReliefRepository()
{
    filePath = "database/relief.txt";
}

std::string ReliefRepository::serialize(
    const Entities::ReliefResource& resource)
{
    return resource.toString();
}

Entities::ReliefResource ReliefRepository::parse(
    const std::string& line)
{
    std::stringstream stream(line);

    std::string id;
    std::string name;
    std::string category;
    std::string quantity;
    std::string unit;

    getline(stream, id, ',');
    getline(stream, name, ',');
    getline(stream, category, ',');
    getline(stream, quantity, ',');
    getline(stream, unit, ',');

    return Entities::ReliefResource(
        std::stoi(id),
        name,
        category,
        std::stoi(quantity),
        unit);
}

bool ReliefRepository::add(
    const Entities::ReliefResource& resource)
{
    std::ofstream file(
        filePath,
        std::ios::app);

    if(!file)
    {
        return false;
    }

    file
        << serialize(resource)
        << "\n";

    return true;
}

std::vector<Entities::ReliefResource>
ReliefRepository::getAll()
{
    std::vector<Entities::ReliefResource> resources;

    std::ifstream file(filePath);

    if(!file)
    {
        return resources;
    }

    std::string line;

    while(getline(file, line))
    {
        if(!line.empty())
        {
            resources.push_back(
                parse(line));
        }
    }

    return resources;
}

bool ReliefRepository::getById(
    int id,
    Entities::ReliefResource& resource)
{
    auto resources = getAll();

    for(auto& item : resources)
    {
        if(item.getId() == id)
        {
            resource = item;
            return true;
        }
    }

    return false;
}

bool ReliefRepository::update(
    const Entities::ReliefResource& resource)
{
    auto resources = getAll();

    bool updated = false;

    for(auto& item : resources)
    {
        if(item.getId() == resource.getId())
        {
            item = resource;
            updated = true;
        }
    }

    if(!updated)
    {
        return false;
    }

    std::ofstream file(filePath);

    for(auto& item : resources)
    {
        file
            << serialize(item)
            << "\n";
    }

    return true;
}

bool ReliefRepository::remove(
    int id)
{
    auto resources = getAll();

    bool removed = false;

    std::vector<Entities::ReliefResource> updatedList;

    for(auto& item : resources)
    {
        if(item.getId() == id)
        {
            removed = true;
        }
        else
        {
            updatedList.push_back(item);
        }
    }

    if(!removed)
    {
        return false;
    }

    std::ofstream file(filePath);

    for(auto& item : updatedList)
    {
        file
            << serialize(item)
            << "\n";
    }

    return true;
}

}
}