#define UNICODE
#define _UNICODE
#include "WinDashboard.h"
#include <string>
#include <sstream>
#include <iomanip>

namespace AgroResQ
{
namespace Graphics
{

static WinDashboard* g_dashboard = nullptr;

WinDashboard::WinDashboard()
{
    g_dashboard = this;
}

WinDashboard::~WinDashboard()
{
    g_dashboard = nullptr;
}

LRESULT CALLBACK WinDashboard::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (g_dashboard && uMsg == WM_CREATE)
    {
        g_dashboard->hMainWindow = hWnd;
        
        g_dashboard->hStatsStatic = CreateWindowEx(
            0, L"STATIC", L"Loading...",
            WS_CHILD | WS_VISIBLE | SS_LEFT,
            20, 20, 600, 350,
            hWnd, NULL, NULL, NULL
        );
      
        g_dashboard->hRefreshButton = CreateWindowEx(
            0, L"BUTTON", L"🔄 Refresh",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            20, 390, 120, 35,
            hWnd, (HMENU)1, NULL, NULL
        );

        g_dashboard->hExitButton = CreateWindowEx(
            0, L"BUTTON", L"✖ Exit",
            WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
            160, 390, 120, 35,
            hWnd, (HMENU)2, NULL, NULL
        );

        g_dashboard->updateStats();
    }

    if (g_dashboard && uMsg == WM_COMMAND)
    {
        if (LOWORD(wParam) == 1)
        {
            g_dashboard->refresh();
        }
        else if (LOWORD(wParam) == 2)
        {
            PostQuitMessage(0);
        }
    }

    if (uMsg == WM_CLOSE)
    {
        DestroyWindow(hWnd);
        return 0;
    }

    if (uMsg == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void WinDashboard::updateStats()
{
    if (!hStatsStatic) return;

    int disasters = reportService.getTotalDisasters();
    int victims = reportService.getTotalVictims();
    int rescued = reportService.getRescuedVictimsCount();
    int missing = reportService.getMissingVictimsCount();
    int shelters = reportService.getTotalShelters();
    int space = reportService.getAvailableShelterSpace();

    std::wstringstream ws;
    
    ws << L"╔══════════════════════════════════════════════════════════╗\n";
    ws << L"║      🌾  AGRO-RESQ DASHBOARD v2.0                     ║\n";
    ws << L"║  Intelligent Disaster Relief & Agriculture             ║\n";
    ws << L"╚══════════════════════════════════════════════════════════╝\n\n";

    ws << L"╔══════════════════════════════════════════════════════════╗\n";
    ws << L"║  📊 REAL-TIME STATISTICS                               ║\n";
    ws << L"╠══════════════════════════════════════════════════════════╣\n";
    
    std::wstringstream num;
    
    ws << L"║  🔥 Disasters     : " << disasters;
    num.str(L""); num << disasters;
    int pad1 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad1; i++) ws << L" ";
    ws << L"║\n";

    ws << L"║  👥 Total Victims : " << victims;
    num.str(L""); num << victims;
    int pad2 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad2; i++) ws << L" ";
    ws << L"║\n";

    ws << L"║  ✅ Rescued       : " << rescued;
    num.str(L""); num << rescued;
    int pad3 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad3; i++) ws << L" ";
    ws << L"║\n";

    ws << L"║  ❌ Missing       : " << missing;
    num.str(L""); num << missing;
    int pad4 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad4; i++) ws << L" ";
    ws << L"║\n";

    ws << L"║  🏠 Shelters      : " << shelters;
    num.str(L""); num << shelters;
    int pad5 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad5; i++) ws << L" ";
    ws << L"║\n";

    ws << L"║  📊 Available     : " << space;
    num.str(L""); num << space;
    int pad6 = 40 - 20 - (int)num.str().length();
    for (int i = 0; i < pad6; i++) ws << L" ";
    ws << L"║\n";

    ws << L"╚══════════════════════════════════════════════════════════╝\n\n";

    if (victims > 0)
    {
        int rescuedPercent = (rescued * 40) / victims;
        if (rescuedPercent > 40) rescuedPercent = 40;
        ws << L"📈 Rescued Progress: [";
        for (int i = 0; i < 40; i++)
        {
            if (i < rescuedPercent)
                ws << L"█";
            else
                ws << L"░";
        }
        ws << L"] " << rescued << L"/" << victims << L"\n";
    }

    if (shelters > 0)
    {
        int spacePercent = (space * 40) / shelters;
        if (spacePercent > 40) spacePercent = 40;
        ws << L"🏠 Shelter Space   : [";
        for (int i = 0; i < 40; i++)
        {
            if (i < spacePercent)
                ws << L"█";
            else
                ws << L"░";
        }
        ws << L"] " << space << L"/" << shelters << L"\n";
    }

    ws << L"\n";

    if (missing > 0)
    {
        ws << L"╔══════════════════════════════════════════════════════════╗\n";
        ws << L"║  ⚠️  ALERT: " << missing << L" victim(s) still missing!          ║\n";
        ws << L"╚══════════════════════════════════════════════════════════╝\n";
    }

    if (space < 10 && shelters > 0)
    {
        ws << L"╔══════════════════════════════════════════════════════════╗\n";
        ws << L"║  ⚠️  WARNING: Shelter space critically low (" << space << L" remaining)! ║\n";
        ws << L"╚══════════════════════════════════════════════════════════╝\n";
    }

    if (missing == 0 && (space >= 10 || shelters == 0))
    {
        ws << L"✅ All systems operational. No critical alerts.\n";
    }

    ws << L"\n🔄 Press 'Refresh' to update  |  ✖ 'Exit' to close";

    SetWindowTextW(hStatsStatic, ws.str().c_str());
}

void WinDashboard::show()
{
    const wchar_t CLASS_NAME[] = L"AgroResQDashboard";

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    hMainWindow = CreateWindowEx(
        0,
        CLASS_NAME,
        L"🌾 AgroResQ Dashboard v2.0",
        WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
        CW_USEDEFAULT, CW_USEDEFAULT, 680, 520,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    ShowWindow(hMainWindow, SW_SHOW);
    UpdateWindow(hMainWindow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void WinDashboard::refresh()
{
    updateStats();
}

}
}