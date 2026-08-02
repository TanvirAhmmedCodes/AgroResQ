#pragma once
#include "../algorithms/AlertSystem.h"

namespace AgroResQ
{
    namespace UI
    {
        class AlertMenu
        {
        private:
            Algorithms::AlertSystem alertSystem;

            void viewAllAlerts();
            void viewUnreadAlerts();
            void markAlertAsRead();
            void markAllAsRead();
            void sendManualAlert();

        public:
            AlertMenu();
            void show();
        };
    }
}