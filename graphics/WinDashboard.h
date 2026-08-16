#pragma once
#include <windows.h>
#include <string>
#include "../services/ReportService.h"

namespace AgroResQ
{
namespace Graphics
{

class WinDashboard
{
private:
    Services::ReportService reportService;
    HWND hMainWindow;
    HWND hStatsStatic;
    HWND hRefreshButton;
    HWND hExitButton;

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void updateStats();

public:
    WinDashboard();
    ~WinDashboard();

    void show();
    void refresh();
};

}
}