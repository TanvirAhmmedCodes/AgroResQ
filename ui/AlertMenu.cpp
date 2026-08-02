#include "AlertMenu.h"
#include "../core/Color.h" 
#include <iostream>

namespace AgroResQ
{
    namespace UI
    {
        AlertMenu::AlertMenu() = default;

        void AlertMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "             ALERT SYSTEM\n";
                std::cout << "=========================================\n";
                std::cout << "1. View All Alerts\n";
                std::cout << "2. View Unread Alerts\n";
                std::cout << "3. Mark Alert as Read\n";
                std::cout << "4. Mark All as Read\n";
                std::cout << "5. Send Manual Alert\n";
                std::cout << "0. Back\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    viewAllAlerts();
                    break;
                case 2:
                    viewUnreadAlerts();
                    break;
                case 3:
                    markAlertAsRead();
                    break;
                case 4:
                    markAllAsRead();
                    break;
                case 5:
                    sendManualAlert();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void AlertMenu::viewAllAlerts()
        {
            alertSystem.displayAlerts();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }

        void AlertMenu::viewUnreadAlerts()
        {
            alertSystem.displayUnreadAlerts();
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }

        void AlertMenu::markAlertAsRead()
        {
            int id;
            std::cout << "\nAlert ID: ";
            std::cin >> id;
            alertSystem.markAsRead(id);
            std::cout << "\nAlert Marked as Read.\n";
        }

        void AlertMenu::markAllAsRead()
        {
            alertSystem.markAllAsRead();
            std::cout << "\nAll Alerts Marked as Read.\n";
        }

        void AlertMenu::sendManualAlert()
        {
            std::string title, message;
            std::cin.ignore();
            std::cout << "\nAlert Title: ";
            getline(std::cin, title);
            std::cout << "Alert Message: ";
            getline(std::cin, message);

            char severityInput;
            std::cout << "Severity (c for Critical, n for Normal): ";
            std::cin >> severityInput;

            if (severityInput == 'c' || severityInput == 'C')
            {
                alertSystem.sendCriticalAlert(title, message);
            }
            else
            {
                alertSystem.sendGeneralAlert(title, message);
            }

            std::cout << "\nAlert Sent Successfully.\n";
        }
    }
}