#include "Weather.h"

#include <sstream>

namespace AgroResQ
{
namespace Entities
{

Weather::Weather()
    : temperature(0.0),
      humidity(0.0),
      rainfall(0.0)
{
}

Weather::Weather(
    int id,
    const std::string& location,
    double temperature,
    double humidity,
    double rainfall)
{
    setId(id);

    this->location = location;
    this->temperature = temperature;
    this->humidity = humidity;
    this->rainfall = rainfall;
}

void Weather::setLocation(const std::string& location)
{
    this->location = location;
}

void Weather::setTemperature(double temperature)
{
    this->temperature = temperature;
}

void Weather::setHumidity(double humidity)
{
    this->humidity = humidity;
}

void Weather::setRainfall(double rainfall)
{
    this->rainfall = rainfall;
}

std::string Weather::getLocation() const
{
    return location;
}

double Weather::getTemperature() const
{
    return temperature;
}

double Weather::getHumidity() const
{
    return humidity;
}

double Weather::getRainfall() const
{
    return rainfall;
}

std::string Weather::toString() const
{
    std::stringstream stream;

    stream << getId() << ","
           << location << ","
           << temperature << ","
           << humidity << ","
           << rainfall;

    return stream.str();
}

}
}