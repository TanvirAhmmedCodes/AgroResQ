#include "ui/MainMenu.h"
#include "hardware/SensorService.h"
#include "core/Color.h"
#include "core/AuthManager.h"
#include "core/TenantManager.h"
#include <iostream>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

int main()
{
    #ifdef _WIN32
        AgroResQ::Core::Color::enableWindowsColors();
    #endif

    // Create database folder
    #ifdef _WIN32
    if (_access("database", 0) != 0) _mkdir("database");
    #else
    struct stat st;
    if (stat("database", &st) != 0) mkdir("database", 0777);
    #endif

    std::cout << AgroResQ::Core::Color::boldCyan()
              << "\n=========================================\n"
              << AgroResQ::Core::Color::boldYellow()
              << "         AGRO RES Q SYSTEM   \n"
              << AgroResQ::Core::Color::boldCyan()
              << "=========================================\n"
              << AgroResQ::Core::Color::reset();

    AgroResQ::Core::AuthManager::initialize();

    
    std::cout << AgroResQ::Core::Color::yellow()
              << "[INFO] Default Admin: admin / admin123\n"
              << AgroResQ::Core::Color::reset();
    

    std::string username, password;
    std::cout << "\nEnter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password;

    if (!AgroResQ::Core::AuthManager::login(username, password))
    {
        std::cout << AgroResQ::Core::Color::red()
                  << "\nLogin failed! Exiting.\n" 
                  << AgroResQ::Core::Color::reset();
        return 1;
    }

    auto user = AgroResQ::Core::AuthManager::getCurrentUser();
    std::cout << AgroResQ::Core::Color::green()
              << "\nWelcome, " << user.username 
              << " (Role: ";
    if (user.role == AgroResQ::Core::UserRole::ADMIN)
        std::cout << "ADMIN)";
    else if (user.role == AgroResQ::Core::UserRole::NGO_OPERATOR)
        std::cout << "NGO)";
    else
        std::cout << "FARMER)";
    std::cout << AgroResQ::Core::Color::reset() << "\n";

    AgroResQ::Core::TenantManager::setCurrentTenant(user.tenantId);
    if (AgroResQ::Core::AuthManager::isAdmin())
        AgroResQ::Core::TenantManager::setAllowedTenants({"ALL"});
    else
        AgroResQ::Core::TenantManager::setAllowedTenants({user.tenantId});

    
    AgroResQ::Hardware::SensorService sensorService(true, "COM3");
    if (sensorService.isSensorConnected())
    {
        std::cout << AgroResQ::Core::Color::green()
                  << "[INFO] " << AgroResQ::Core::Color::reset()
                  << sensorService.getSensorInfo() << " detected.\n";
    }
    else
    {
        std::cout << AgroResQ::Core::Color::yellow()
                  << "[INFO] " << AgroResQ::Core::Color::reset()
                  << "No sensor detected. Using simulated data.\n";
        sensorService.reconnect(false);
        std::cout << AgroResQ::Core::Color::green()
                  << "[INFO] " << AgroResQ::Core::Color::reset()
                  << "Using " << sensorService.getSensorInfo() << "\n";
    }

    AgroResQ::UI::MainMenu mainMenu;
    mainMenu.show();

    return 0;
}