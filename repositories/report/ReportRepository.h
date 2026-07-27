#pragma once

#include <vector>
#include <string>

#include "../../entities/Report.h"
#include "../../core/FileManager.h"


namespace AgroResQ
{
namespace Repositories
{

class ReportRepository
{

private:

    std::string filePath;

    Core::FileManager fileManager;



    Entities::Report parse(
        const std::string& line);



    std::string serialize(
        const Entities::Report& report);



public:

    ReportRepository();



    bool add(
        const Entities::Report& report);



    std::vector<Entities::Report> getAll();



    bool getById(
        int id,
        Entities::Report& report);



    bool update(
        const Entities::Report& report);



    bool remove(
        int id);

};

}
}