#pragma once
#include "../data_structures/Graph.h"
#include <string>

namespace AgroResQ
{
    namespace UI
    {
        class RouteOptimizationMenu
        {
        private:
            DataStructures::Graph graph;

            void buildGraph();
            void findRoute();
            void displayAllRoutes();
            void addLocation();
            void addRoute();

        public:
            RouteOptimizationMenu();
            void show();
        };
    }
}