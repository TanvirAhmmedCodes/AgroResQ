#include "ReportRepository.h"

#include <fstream>
#include <sstream>


namespace AgroResQ
{
namespace Repositories
{


ReportRepository::ReportRepository()
{

    filePath = "database/reports.txt";

}






std::string ReportRepository::serialize(
    const Entities::Report& report)
{

    return report.toString();

}






Entities::Report ReportRepository::parse(
    const std::string& line)
{

    std::stringstream stream(line);


    std::string id;

    std::string title;

    std::string description;

    std::string date;



    getline(stream,id,',');

    getline(stream,title,',');

    getline(stream,description,',');

    getline(stream,date,',');




    return Entities::Report(
        std::stoi(id),
        title,
        description,
        date);

}








bool ReportRepository::add(
    const Entities::Report& report)
{

    std::ofstream file(
        filePath,
        std::ios::app);



    if(!file)
        return false;



    file
    << serialize(report)
    << "\n";



    return true;

}








std::vector<Entities::Report> ReportRepository::getAll()
{

    std::vector<Entities::Report> reports;


    std::ifstream file(filePath);



    if(!file)
        return reports;



    std::string line;



    while(getline(file,line))
    {

        if(!line.empty())
        {

            reports.push_back(
                parse(line));

        }

    }



    return reports;

}








bool ReportRepository::getById(
    int id,
    Entities::Report& report)
{

    auto reports = getAll();



    for(auto& item : reports)
    {

        if(item.getId() == id)
        {

            report = item;

            return true;

        }

    }



    return false;

}








bool ReportRepository::update(
    const Entities::Report& report)
{

    auto reports = getAll();


    bool updated = false;



    for(auto& item : reports)
    {

        if(item.getId() == report.getId())
        {

            item = report;

            updated = true;

        }

    }



    if(!updated)
        return false;




    std::ofstream file(filePath);



    for(auto& item : reports)
    {

        file
        << serialize(item)
        << "\n";

    }



    return true;

}








bool ReportRepository::remove(
    int id)
{

    auto reports = getAll();


    bool removed = false;


    std::vector<Entities::Report> updatedReports;



    for(auto& item : reports)
    {

        if(item.getId() == id)
        {

            removed = true;

        }
        else
        {

            updatedReports.push_back(item);

        }

    }



    if(!removed)
        return false;



    std::ofstream file(filePath);



    for(auto& item : updatedReports)
    {

        file
        << serialize(item)
        << "\n";

    }



    return true;

}



}
}