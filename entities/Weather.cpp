#include "Weather.h"
#include <sstream>

namespace AgroResQ
{
namespace Entities
{
    Weather::Weather() : temperature(0.0), humidity(0.0), rainfall(0.0) {}

    Weather::Weather(int id, const std::string& location, double temperature,
                     double humidity, double rainfall, const std::string& tenantId)
    {
        setId(id);
        this->location = location;
        this->temperature = temperature;
        this->humidity = humidity;
        this->rainfall = rainfall;
        this->tenantId = tenantId;
    }

    void Weather::setLocation(const std::string& location) { this->location = location; }
    void Weather::setTemperature(double temperature) { this->temperature = temperature; }
    void Weather::setHumidity(double humidity) { this->humidity = humidity; }
    void Weather::setRainfall(double rainfall) { this->rainfall = rainfall; }
    void Weather::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

    std::string Weather::getLocation() const { return location; }
    double Weather::getTemperature() const { return temperature; }
    double Weather::getHumidity() const { return humidity; }
    double Weather::getRainfall() const { return rainfall; }
    std::string Weather::getTenantId() const { return tenantId; }

    std::string Weather::toString() const
    {
        std::stringstream ss;
        ss << getId() << "," << location << "," << temperature << ","
           << humidity << "," << rainfall << "," << tenantId;
        return ss.str();
    }
}
}