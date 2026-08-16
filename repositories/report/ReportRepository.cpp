#include "ReportRepository.h"
#include "../../core/StringHelper.h"
#include "../../security/XORCipher.h"
#include <sstream>

namespace AgroResQ
{
namespace Repositories
{
    ReportRepository::ReportRepository()
    {
        filePath = "database/reports.txt";
        rebuildCache();
    }

    void ReportRepository::rebuildCache()
    {
        reportCache.clear();
        auto reports = getAll();
        for (const auto& r : reports)
        {
            reportCache.add(r.getId(), r);
        }
    }

    Entities::Report ReportRepository::parse(const std::string& line) const
    {
        Security::XORCipher cipher;
        std::string decrypted = cipher.decrypt(line);
        std::string dataToParse = decrypted.empty() ? line : decrypted;

        std::stringstream ss(dataToParse);
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
        Security::XORCipher cipher;
        std::string encrypted = cipher.encrypt(report.toString());
        bool ok = fileManager.appendFile(filePath, encrypted + "\n");
        if (ok)
        {
            reportCache.add(report.getId(), report);
        }
        return ok;
    }

    bool ReportRepository::update(const Entities::Report& report)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (auto& r : all)
        {
            if (r.getId() == report.getId())
            {
                r = report;
                found = true;
            }
            data += cipher.encrypt(r.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            reportCache.add(report.getId(), report);
        }
        return ok;
    }

    bool ReportRepository::remove(int id)
    {
        auto all = getAll();
        bool found = false;
        std::string data;
        Security::XORCipher cipher;

        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                found = true;
                continue;
            }
            data += cipher.encrypt(r.toString()) + "\n";
        }

        if (!found) return false;
        bool ok = fileManager.writeFile(filePath, data);
        if (ok)
        {
            reportCache.remove(id);
        }
        return ok;
    }

    bool ReportRepository::getById(int id, Entities::Report& report)
    {
        if (reportCache.get(id, report))
            return true;

        auto all = getAll();
        for (const auto& r : all)
        {
            if (r.getId() == id)
            {
                report = r;
                reportCache.add(id, r);
                return true;
            }
        }
        return false;
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