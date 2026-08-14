#include "ReportRepository.h"
#include "../../core/StringHelper.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    ReportRepository::ReportRepository()
    {
        filePath = "database/reports.txt";
    }

    Entities::Report ReportRepository::parse(const std::string& line) const
    {
        std::stringstream ss(line);
        std::string id, title, description, date, tenantId;
        std::getline(ss, id, ',');
        std::getline(ss, title, ',');
        std::getline(ss, description, ',');
        std::getline(ss, date, ',');
        std::getline(ss, tenantId);
        return Entities::Report(
            Core::safeStoi(id),
            title, description, date,
            tenantId
        );
    }

    bool ReportRepository::add(const Entities::Report& report)
    {
        return fileManager.appendFile(filePath, report.toString() + "\n");
    }

    std::vector<Entities::Report> ReportRepository::getAll()
    {
        std::vector<Entities::Report> reports;
        std::vector<std::string> lines = fileManager.readLines(filePath);
        for (const auto& line : lines)
        {
            if (!line.empty())
                reports.push_back(parse(line));
        }
        return reports;
    }

    bool ReportRepository::getById(int id, Entities::Report& report)
    {
        auto all = getAll();
        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                report = r;
                return true;
            }
        }
        return false;
    }

    bool ReportRepository::update(const Entities::Report& report)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (auto& r : all)
        {
            if (r.getId() == report.getId())
            {
                r = report;
                found = true;
            }
            data += r.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    bool ReportRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                found = true;
                continue;
            }
            data += r.toString() + "\n";
        }
        if (!found) return false;
        return fileManager.writeFile(filePath, data);
    }

    std::vector<Entities::Report> ReportRepository::getByTenant(const std::string& tenantId)
    {
        std::vector<Entities::Report> result;
        auto all = getAll();
        for (const auto& r : all)
        {
            if (r.getTenantId() == tenantId || tenantId == "ALL")
                result.push_back(r);
        }
        return result;
    }
}
}