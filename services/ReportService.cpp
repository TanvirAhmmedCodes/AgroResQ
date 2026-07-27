#include "ReportService.h"
#include "../repositories/victim/VictimRepository.h"
#include "../repositories/disaster/DisasterRepository.h"
#include "../repositories/disaster/ShelterRepository.h"

namespace AgroResQ
{
    namespace Services
    {

        ReportService::ReportService() = default;

        bool ReportService::addReport(
            const std::string &title,
            const std::string &description,
            const std::string &date)
        {

            if (title.empty())
                return false;

            if (description.empty())
                return false;

            int id =
                idGenerator.generateNextId(
                    "database/reports.txt");

            Entities::Report report(
                id,
                title,
                description,
                date);

            return reportRepository.add(report);
        }

        bool ReportService::updateReport(
            int id,
            const std::string &title,
            const std::string &description,
            const std::string &date)
        {

            if (title.empty())
                return false;

            if (description.empty())
                return false;

            Entities::Report report(
                id,
                title,
                description,
                date);

            return reportRepository.update(report);
        }

        bool ReportService::deleteReport(
            int id)
        {

            return reportRepository.remove(id);
        }

        bool ReportService::searchReport(
            int id,
            Entities::Report &report)
        {

            return reportRepository.getById(
                id,
                report);
        }

        std::vector<Entities::Report> ReportService::getAllReports()
        {

            return reportRepository.getAll();
        }
        int ReportService::getTotalVictims()
        {
            Repositories::VictimRepository repo;

            return repo.getAll().size();
        }

        int ReportService::getMissingVictimsCount()
        {
            Repositories::VictimRepository repo;

            int count = 0;

            for (auto &victim : repo.getAll())
            {
                if (victim.isMissing())
                {
                    count++;
                }
            }

            return count;
        }

        int ReportService::getRescuedVictimsCount()
        {
            Repositories::VictimRepository repo;

            int count = 0;

            for (auto &victim : repo.getAll())
            {
                if (victim.isRescued())
                {
                    count++;
                }
            }

            return count;
        }

        int ReportService::getReliefReceivedCount()
        {
            Repositories::VictimRepository repo;

            int count = 0;

            for (auto &victim : repo.getAll())
            {
                if (victim.hasReliefReceived())
                {
                    count++;
                }
            }

            return count;
        }

        int ReportService::getTotalDisasters()
        {
            Repositories::DisasterRepository repo;

            return repo.getAll().size();
        }

        int ReportService::getTotalShelters()
        {
            Repositories::ShelterRepository repo;

            return repo.getAll().size();
        }

        int ReportService::getAvailableShelterSpace()
        {
            Repositories::ShelterRepository repo;

            int total = 0;

            for (auto &shelter : repo.getAll())
            {
                total += shelter.getCapacity() - shelter.getOccupied();
            }

            return total;
        }

    }
}