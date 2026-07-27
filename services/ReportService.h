#pragma once

#include <vector>

#include "../core/IDGenerator.h"

#include "../entities/Report.h"

#include "../repositories/report/ReportRepository.h"


namespace AgroResQ
{
namespace Services
{

class ReportService
{

private:

    Repositories::ReportRepository reportRepository;

    Core::IDGenerator idGenerator;



public:

    ReportService();



    bool addReport(
        const std::string& title,
        const std::string& description,
        const std::string& date);



    bool updateReport(
        int id,
        const std::string& title,
        const std::string& description,
        const std::string& date);



    bool deleteReport(
        int id);



    bool searchReport(
        int id,
        Entities::Report& report);



    std::vector<Entities::Report> getAllReports();
    int getTotalVictims();

int getMissingVictimsCount();

int getRescuedVictimsCount();

int getReliefReceivedCount();

int getTotalDisasters();

int getTotalShelters();

int getAvailableShelterSpace();

};

}
}