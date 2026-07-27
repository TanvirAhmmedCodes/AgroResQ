#include "ui/MainMenu.h"
#include "hardware/SensorService.h"
#include "core/Color.h"
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
    // ===== Windows Color Enable =====
    #ifdef _WIN32
        AgroResQ::Core::Color::enableWindowsColors();
    #endif

    // ===== Database Folder Create =====
    #ifdef _WIN32
    if (_access("database", 0) != 0)
    {
        _mkdir("database");
    }
    #else
    struct stat st;
    if (stat("database", &st) != 0)
    {
        mkdir("database", 0777);
    }
    #endif

    // ===== Welcome Banner with Colors =====
    std::cout << AgroResQ::Core::Color::boldCyan()
              << "\n=========================================\n"
              << AgroResQ::Core::Color::boldYellow()
              << "         AGRO RES Q SYSTEM   \n"
              << AgroResQ::Core::Color::boldCyan()
              << "=========================================\n"
              << AgroResQ::Core::Color::reset();

    // ===== Sensor Detection =====
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

    // ===== Main Menu =====
    AgroResQ::UI::MainMenu mainMenu;
    mainMenu.show();

    return 0;
}