#include "AgricultureMenu.h"
#include "../core/TenantManager.h"
#include "../core/AuthManager.h"
#include "../repositories/agriculture/CropRepository.h"
#include <iostream>
#include <algorithm>

namespace AgroResQ
{
    namespace UI
    {
        AgricultureMenu::AgricultureMenu() : sensorService(true, "COM3") {}

        void AgricultureMenu::show()
        {
            int choice;

            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "          AGRICULTURE MANAGEMENT\n";
                std::cout << "=========================================\n";
                std::cout << "1. Farm Management\n";
                std::cout << "2. Soil Management\n";
                std::cout << "3. Weather Management\n";
                std::cout << "4. Crop Management\n";
                std::cout << "5. Decision Support\n";
                std::cout << "6. Crop Recommendation (AI Based)\n";
                std::cout << "7. Read Data from Sensor\n";
                std::cout << "8. Sync Sensor Data to Database\n";
                
                std::cout << "0. Back\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";

                std::cin >> choice;

                switch (choice)
                {
                case 1: farmMenu.show(); break;
                case 2: soilMenu.show(); break;
                case 3: weatherMenu.show(); break;
                case 4: cropMenu.show(); break;
                case 5: decisionSupportMenu.show(); break;
                case 6: recommendCrop(); break;
                case 7: readFromSensor(); break;
                case 8: syncSensorData(); break;
              
                case 0: break;
                default: std::cout << "\nInvalid Choice.\n";
                }

            } while (choice != 0);
        }

        void AgricultureMenu::recommendCrop()
        {
            std::string soilType;
            double phLevel;
            double moisture;

            std::cin.ignore();

            std::cout << "\n========== CROP RECOMMENDATION ENGINE ==========\n";
            std::cout << "Enter Soil Type (e.g., Loamy, Clay, Sandy): ";
            std::getline(std::cin, soilType);
            std::cout << "Enter Soil pH Level (0-14): ";
            std::cin >> phLevel;
            std::cout << "Enter Soil Moisture (%): ";
            std::cin >> moisture;

            std::string currentTenant = Core::TenantManager::getCurrentTenant();
            std::vector<Entities::Crop> crops;
            if (Core::AuthManager::isAdmin())
                crops = cropService.getAllCrops();
            else {
                Repositories::CropRepository repo;
                crops = repo.getByTenant(currentTenant);
            }

            if (crops.empty())
            {
                std::cout << "\n[ERROR] No crops found in database. Please add crops first.\n";
                return;
            }

            std::vector<std::pair<double, Entities::Crop>> scoredCrops;

            for (const auto& crop : crops)
            {
                double score = 0.0;

                if (crop.getSuitableSoil() == soilType)
                {
                    score += 50;
                }

                if (phLevel >= 5.0 && phLevel <= 8.0)
                {
                    score += 25;
                }

                if (moisture >= 30.0 && moisture <= 70.0)
                {
                    score += 25;
                }

                scoredCrops.push_back(std::make_pair(score, crop));
            }

            // ===== FIX: Use explicit type instead of generic lambda =====
            std::sort(
                scoredCrops.begin(),
                scoredCrops.end(),
                [](const std::pair<double, Entities::Crop>& a,
                   const std::pair<double, Entities::Crop>& b) -> bool
                {
                    return a.first > b.first;
                });
            // ============================================================

            std::cout << "\n========== RECOMMENDED CROPS (Ranked) ==========\n";
            int rank = 1;
            for (std::vector<std::pair<double, Entities::Crop>>::const_iterator it = scoredCrops.begin(); it != scoredCrops.end(); ++it)
            {
                const std::pair<double, Entities::Crop>& item = *it;
                std::cout << "#" << rank++
                          << " | Crop: " << item.second.getCropName()
                          << " | Score: " << item.first
                          << " | Season: " << item.second.getSeason()
                          << " | Soil: " << item.second.getSuitableSoil()
                          << "\n";
            }

            if (!scoredCrops.empty() && scoredCrops.front().first == 0)
            {
                std::cout << "\n[INFO] No crop perfectly matches. Showing all available crops.\n";
            }

            std::cout << "==================================================\n";
        }

        void AgricultureMenu::readFromSensor()
        {
            std::cout << "\n========== SENSOR DATA READING ==========\n";
            std::cout << "Sensor: " << sensorService.getSensorInfo() << "\n";

            if (!sensorService.isSensorConnected())
            {
                std::cout << "[ERROR] Sensor not connected. Trying to reconnect...\n";
                sensorService.reconnect(true, "COM3");
                
                if (!sensorService.isSensorConnected())
                {
                    std::cout << "[ERROR] Failed to connect. Switching to simulated mode.\n";
                    sensorService.reconnect(false);
                }
            }

            auto data = sensorService.readAllData();

            if (data.valid)
            {
                std::cout << "\n--- SENSOR READINGS ---\n";
                std::cout << "Soil Moisture : " << data.moisture << "%\n";
                std::cout << "Soil pH Level : " << data.ph << "\n";
                std::cout << "Temperature   : " << data.temperature << "°C\n";
                std::cout << "Humidity      : " << data.humidity << "%\n";

                char saveChoice;
                std::cout << "\nSave to database? (y/n): ";
                std::cin >> saveChoice;

                if (saveChoice == 'y' || saveChoice == 'Y')
                {
                    std::string farmId, soilType;
                    std::cin.ignore();
                    std::cout << "Farm ID: ";
                    std::getline(std::cin, farmId);
                    std::cout << "Soil Type: ";
                    std::getline(std::cin, soilType);

                    Services::SoilService soilService;
                    if (soilService.addSoil(farmId, data.ph, data.moisture, soilType))
                    {
                        std::cout << "\nSoil Data Saved Successfully.\n";
                    }
                    else
                    {
                        std::cout << "\nFailed to Save Soil Data.\n";
                    }

                    Services::WeatherService weatherService;
                    if (weatherService.addWeather(farmId, data.temperature, data.humidity, 0))
                    {
                        std::cout << "Weather Data Saved Successfully.\n";
                    }
                    else
                    {
                        std::cout << "Failed to Save Weather Data.\n";
                    }
                }
            }
            else
            {
                std::cout << "\n[ERROR] Failed to read sensor data.\n";
                std::cout << "Make sure Arduino is connected and sending data in format:\n";
                std::cout << "moisture,ph,temperature,humidity\n";
            }

            std::cout << "=============================================\n";
        }

        void AgricultureMenu::syncSensorData()
        {
            std::cout << "\n========== SENSOR DATA SYNC ==========\n";
            std::cout << "Sensor: " << syncService.getSensorInfo() << "\n";

            bool success = syncService.syncOnce();

            if (success)
            {
                std::cout << "\n[SUCCESS] Sensor data synced to database.\n";
            }
            else
            {
                std::cout << "\n[FAILED] Could not sync sensor data.\n";
            }

            std::cout << "=========================================\n";
        }
    }
}