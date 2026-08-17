#pragma once
#include "FarmMenu.h"
#include "SoilMenu.h"
#include "WeatherMenu.h"
#include "CropMenu.h"
#include "DecisionSupportMenu.h"
#include "../services/CropService.h"
#include "../hardware/SensorService.h"
#include "../services/SensorSyncService.h"

namespace AgroResQ
{
    namespace UI
    {
        class AgricultureMenu
        {
        private:
            FarmMenu farmMenu;
            SoilMenu soilMenu;
            WeatherMenu weatherMenu;
            CropMenu cropMenu;
            DecisionSupportMenu decisionSupportMenu;
            Services::CropService cropService;
            Hardware::SensorService sensorService;
            Services::SensorSyncService syncService; 

            void recommendCrop();
            void readFromSensor();
            void syncSensorData(); 
            void startAutoSync(); 

        public:
            AgricultureMenu();
            void show();
        };
    }
}