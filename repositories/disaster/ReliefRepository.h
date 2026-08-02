#pragma once

#include <vector>
#include <string>

#include "../../entities/ReliefResource.h"
#include "../../core/FileManager.h"

namespace AgroResQ
{
namespace Repositories
{

class ReliefRepository
{
private:

    std::string filePath;

    Core::FileManager fileManager;

    Entities::ReliefResource parse(
        const std::string& line);

    std::string serialize(
        const Entities::ReliefResource& resource);

public:

    ReliefRepository();

    bool add(
        const Entities::ReliefResource& resource);

    std::vector<Entities::ReliefResource> getAll();

    bool getById(
        int id,
        Entities::ReliefResource& resource);

    bool update(
        const Entities::ReliefResource& resource);

    bool remove(
        int id);
};

}
}