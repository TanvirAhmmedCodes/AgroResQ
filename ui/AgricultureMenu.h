#pragma once
#include "FarmMenu.h"
#include "SoilMenu.h"
#include "WeatherMenu.h"
#include "CropMenu.h"
#include "DecisionSupportMenu.h"
#include "../services/CropService.h"
#include "../hardware/SensorService.h"

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

            void recommendCrop();
            void readFromSensor();

        public:
            AgricultureMenu();
            void show();
        };
    }
}