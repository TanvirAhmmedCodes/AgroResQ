#include "VictimRepository.h"

#include <fstream>
#include <sstream>


namespace AgroResQ
{
namespace Repositories
{


VictimRepository::VictimRepository()
{
    filePath = "database/victims.txt";
}



std::string VictimRepository::serialize(
    const Entities::Victim& victim)
{

    return victim.toString();

}



Entities::Victim VictimRepository::parse(
    const std::string& line)
{

    std::stringstream stream(line);


    std::string id;
    std::string name;
    std::string age;
    std::string gender;
    std::string address;
    std::string vulnerable;
    std::string familyId;
std::string healthStatus;
std::string disabled;
std::string rescued;
std::string reliefReceived;
std::string missing;
std::string priorityScore;
std::string shelterId;



    getline(stream,id,',');
    getline(stream,name,',');
    getline(stream,age,',');
    getline(stream,gender,',');
    getline(stream,address,',');
    getline(stream,vulnerable,',');
    getline(stream, familyId, ',');
getline(stream, healthStatus, ',');
getline(stream, disabled, ',');
getline(stream, rescued, ',');
getline(stream, reliefReceived, ',');
getline(stream, missing, ',');
getline(stream, priorityScore, ',');
getline(stream, shelterId, ',');



    return Entities::Victim(
    std::stoi(id),
    name,
    std::stoi(age),
    gender,
    address,
    vulnerable == "1",
    familyId.empty() ? 0 : std::stoi(familyId),
    healthStatus,
    disabled == "1",
    rescued == "1",
    reliefReceived == "1",
    missing == "1",
    priorityScore.empty() ? 0 : std::stoi(priorityScore),
    shelterId.empty() ? 0 : std::stoi(shelterId));
}



bool VictimRepository::add(
    const Entities::Victim& victim)
{

    std::ofstream file(
        filePath,
        std::ios::app);


    if(!file)
        return false;



    file
        << serialize(victim)
        << "\n";


    return true;
}



std::vector<Entities::Victim> VictimRepository::getAll()
{

    std::vector<Entities::Victim> victims;


    std::ifstream file(filePath);


    if(!file)
        return victims;



    std::string line;


    while(getline(file,line))
    {

        if(!line.empty())
        {
            victims.push_back(
                parse(line));
        }

    }


    return victims;
}



bool VictimRepository::getById(
    int id,
    Entities::Victim& victim)
{

    auto victims = getAll();



    for(auto& item : victims)
    {

        if(item.getId() == id)
        {
            victim = item;
            return true;
        }

    }


    return false;
}



bool VictimRepository::update(
    const Entities::Victim& victim)
{

    auto victims = getAll();


    bool updated = false;



    for(auto& item : victims)
    {

        if(item.getId() == victim.getId())
        {
            item = victim;
            updated = true;
        }

    }



    if(!updated)
        return false;



    std::ofstream file(filePath);



    for(auto& item : victims)
    {

        file
            << serialize(item)
            << "\n";

    }



    return true;
}



bool VictimRepository::remove(
    int id)
{

    auto victims = getAll();


    bool removed = false;



    std::vector<Entities::Victim> updatedList;



    for(auto& item : victims)
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