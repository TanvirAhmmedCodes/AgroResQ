#include "ShelterRepository.h"

#include <fstream>
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{

ShelterRepository::ShelterRepository()
{
    filePath = "database/shelters.txt";
}

std::string ShelterRepository::serialize(
    const Entities::Shelter& shelter)
{
    return shelter.toString();
}

Entities::Shelter ShelterRepository::parse(
    const std::string& line)
{
    std::stringstream stream(line);

    std::string id;
    std::string name;
    std::string location;
    std::string capacity;
    std::string occupied;

    getline(stream, id, ',');
    getline(stream, name, ',');
    getline(stream, location, ',');
    getline(stream, capacity, ',');
    getline(stream, occupied, ',');

    return Entities::Shelter(
        std::stoi(id),
        name,
        location,
        std::stoi(capacity),
        std::stoi(occupied));
}

bool ShelterRepository::add(
    const Entities::Shelter& shelter)
{
    std::ofstream file(
        filePath,
        std::ios::app);

    if(!file)
        return false;

    file
        << serialize(shelter)
        << "\n";

    return true;
}

std::vector<Entities::Shelter> ShelterRepository::getAll()
{
    std::vector<Entities::Shelter> shelters;

    std::ifstream file(filePath);

    if(!file)
        return shelters;

    std::string line;

    while(getline(file, line))
    {
        if(!line.empty())
        {
            shelters.push_back(
                parse(line));
        }
    }

    return shelters;
}

bool ShelterRepository::getById(
    int id,
    Entities::Shelter& shelter)
{
    auto shelters = getAll();

    for(auto& item : shelters)
    {
        if(item.getId() == id)
        {
            shelter = item;
            return true;
        }
    }

    return false;
}

bool ShelterRepository::update(
    const Entities::Shelter& shelter)
{
    auto shelters = getAll();

    bool updated = false;

    for(auto& item : shelters)
    {
        if(item.getId() == shelter.getId())
        {
            item = shelter;
            updated = true;
        }
    }

    if(!updated)
        return false;

    std::ofstream file(filePath);

    for(auto& item : shelters)
    {
        file
            << serialize(item)
            << "\n";
    }

    return true;
}

bool ShelterRepository::remove(
    int id)
{
    auto shelters = getAll();

    bool removed = false;

    std::vector<Entities::Shelter> updatedList;

    for(auto& item : shelters)
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
        return false;

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