#pragma once
#include "../graphics/WinDashboard.h"

namespace AgroResQ
{
namespace UI
{

class GraphicalDashboard
{
private:
    Graphics::WinDashboard winDashboard;

public:
    GraphicalDashboard() = default;
    ~GraphicalDashboard() = default;

    void show() { winDashboard.show(); }
    void refresh() { winDashboard.refresh(); }
};

}
}