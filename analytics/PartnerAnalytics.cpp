#include "PartnerAnalytics.h"
#include "../repositories/agriculture/SoilRepository.h"
#include "../repositories/agriculture/WeatherRepository.h"
#include "../repositories/victim/VictimRepository.h"
#include <sstream>
#include <ctime>
#include <iomanip>

namespace AgroResQ
{
namespace Analytics
{
PartnerAnalytics::PartnerAnalytics() {}

double PartnerAnalytics::calculateAverage(const std::vector<double>& values)
{
    if (values.empty()) return 0.0;
    double sum = 0.0;
    for (double v : values) sum += v;
    return sum / values.size();
}

AggregatedReport PartnerAnalytics::aggregate(const std::string& region, const std::string& tenantId)
{
    AggregatedReport report;
    report.region = region;

    Repositories::SoilRepository soilRepo;
    Repositories::WeatherRepository weatherRepo;
    Repositories::VictimRepository victimRepo;

    std::vector<double> phs, moistures, temps, humidities;

    std::vector<Entities::Soil> soils;
    if (tenantId.empty() || tenantId == "ALL")
        soils = soilRepo.getAll();
    else
        soils = soilRepo.getByTenant(tenantId);

    for (const auto& s : soils)
    {
        if (s.getFarmId() == region || region.empty())
        {
            phs.push_back(s.getPhLevel());
            moistures.push_back(s.getMoisture());
        }
    }

    std::vector<Entities::Weather> weathers;
    if (tenantId.empty() || tenantId == "ALL")
        weathers = weatherRepo.getAll();
    else
        weathers = weatherRepo.getByTenant(tenantId);

    for (const auto& w : weathers)
    {
        if (w.getLocation() == region || region.empty())
        {
            temps.push_back(w.getTemperature());
            humidities.push_back(w.getHumidity());
        }
    }

    report.avgPh = calculateAverage(phs);
    report.avgMoisture = calculateAverage(moistures);
    report.avgTemp = calculateAverage(temps);
    report.avgHumidity = calculateAverage(humidities);

    std::vector<Entities::Victim> victims;
    if (tenantId.empty() || tenantId == "ALL")
        victims = victimRepo.getAll();
    else
        victims = victimRepo.getByTenant(tenantId);

    report.totalVictims = victims.size();
    int displaced = 0;
    for (const auto& v : victims)
    {
        if (v.isMissing() || v.getShelterId() > 0) displaced++;
    }
    report.totalDisplaced = displaced;

    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    report.timestamp = std::string(buf);

    return report;
}

std::string PartnerAnalytics::generateCsvReport(const std::string& region, const std::string& tenantId)
{
    auto report = aggregate(region, tenantId);
    std::stringstream ss;
    ss << "Region,AvgPH,AvgMoisture,AvgTemp,AvgHumidity,TotalVictims,Displaced,Timestamp\n";
    ss << report.region << ","
       << report.avgPh << ","
       << report.avgMoisture << ","
       << report.avgTemp << ","
       << report.avgHumidity << ","
       << report.totalVictims << ","
       << report.totalDisplaced << ","
       << report.timestamp << "\n";
    return ss.str();
}

std::string PartnerAnalytics::generateJsonReport(const std::string& region, const std::string& tenantId)
{
    auto report = aggregate(region, tenantId);
    std::stringstream ss;
    ss << "{\n";
    ss << "  \"region\": \"" << report.region << "\",\n";
    ss << "  \"avgPh\": " << report.avgPh << ",\n";
    ss << "  \"avgMoisture\": " << report.avgMoisture << ",\n";
    ss << "  \"avgTemp\": " << report.avgTemp << ",\n";
    ss << "  \"avgHumidity\": " << report.avgHumidity << ",\n";
    ss << "  \"totalVictims\": " << report.totalVictims << ",\n";
    ss << "  \"totalDisplaced\": " << report.totalDisplaced << ",\n";
    ss << "  \"timestamp\": \"" << report.timestamp << "\"\n";
    ss << "}";
    return ss.str();
}

}
}