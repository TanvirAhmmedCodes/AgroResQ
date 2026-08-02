#pragma once

#include <vector>
#include <string>

#include "../../entities/RescueTeam.h"
#include "../../core/FileManager.h"

namespace AgroResQ
{
namespace Repositories
{

class RescueTeamRepository
{
private:

    std::string filePath;

    Core::FileManager fileManager;

    Entities::RescueTeam parse(
        const std::string& line);

    std::string serialize(
        const Entities::RescueTeam& team);

public:

    RescueTeamRepository();

    bool add(
        const Entities::RescueTeam& team);

    std::vector<Entities::RescueTeam> getAll();

    bool getById(
        int id,
        Entities::RescueTeam& team);

    bool update(
        const Entities::RescueTeam& team);

    bool remove(
        int id);
};

}
}