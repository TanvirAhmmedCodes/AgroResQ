#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Weather : public Core::BaseEntity
        {
        private:
            std::string location;
            double temperature;
            double humidity;
            double rainfall;
            std::string tenantId;

        public:
            Weather();
            Weather(int id, const std::string& location, double temperature,
                    double humidity, double rainfall, const std::string& tenantId = "");

            void setLocation(const std::string& location);
            void setTemperature(double temperature);
            void setHumidity(double humidity);
            void setRainfall(double rainfall);
            void setTenantId(const std::string& tenantId);

            std::string getLocation() const;
            double getTemperature() const;
            double getHumidity() const;
            double getRainfall() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}