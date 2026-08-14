#include "ui/MainMenu.h"
#include "hardware/SensorService.h"
#include "core/Color.h"
#include "core/AuthManager.h"
#include "core/TenantManager.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#include <windows.h>
#define mkdir _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

std::string getExeDirectory()
{
    #ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string exePath = buffer;
    size_t pos = exePath.find_last_of("\\/");
    return exePath.substr(0, pos + 1);
    #else
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
    if (len != -1) {
        buffer[len] = '\0';
        std::string exePath = buffer;
        size_t pos = exePath.find_last_of("/");
        return exePath.substr(0, pos + 1);
    }
    return "./";
    #endif
}

void ensureDatabase()
{
    std::string dbPath = getExeDirectory() + "database";
    
    // Create database folder if not exists
    #ifdef _WIN32
    if (_access(dbPath.c_str(), 0) != 0)
    {
        _mkdir(dbPath.c_str());
    }
    #else
    struct stat st;
    if (stat(dbPath.c_str(), &st) != 0)
    {
        mkdir(dbPath.c_str(), 0777);
    }
    #endif

    std::string usersPath = dbPath + "/users.txt";
    #ifdef _WIN32
    if (_access(usersPath.c_str(), 0) != 0)
    #else
    if (stat(usersPath.c_str(), &st) != 0)
    #endif
    {
        std::ofstream usersFile(usersPath);
        usersFile << "1,admin,P1kAlMiG:4283eee1,ADMIN,ALL\n";
        usersFile.close();
        std::cout << "[INFO] Default users.txt created.\n";
    }
}

int main()
{
    #ifdef _WIN32
        AgroResQ::Core::Color::enableWindowsColors();
    #endif


    ensureDatabase();


    std::cout << AgroResQ::Core::Color::boldCyan()
              << "\n=========================================\n"
              << AgroResQ::Core::Color::boldYellow()
              << "         AGRO RES Q SYSTEM   \n"
              << AgroResQ::Core::Color::boldCyan()
              << "=========================================\n"
              << AgroResQ::Core::Color::reset();


    std::string usersPath = getExeDirectory() + "database/users.txt";
    AgroResQ::Core::AuthManager::initialize(usersPath);


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