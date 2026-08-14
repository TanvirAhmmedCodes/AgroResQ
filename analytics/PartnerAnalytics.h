#pragma once
#include <string>
#include <vector>
#include "../entities/Soil.h"
#include "../entities/Weather.h"
#include "../entities/Victim.h"

namespace AgroResQ
{
namespace Analytics
{
struct AggregatedReport
{
    std::string region;
    double avgPh;
    double avgMoisture;
    double avgTemp;
    double avgHumidity;
    int totalVictims;
    int totalDisplaced;
    std::string timestamp;
};

class PartnerAnalytics
{
public:
    PartnerAnalytics();

    std::string generateCsvReport(const std::string& region, const std::string& tenantId = "");
    std::string generateJsonReport(const std::string& region, const std::string& tenantId = "");
    AggregatedReport aggregate(const std::string& region, const std::string& tenantId = "");

private:
    double calculateAverage(const std::vector<double>& values);
};
}
}