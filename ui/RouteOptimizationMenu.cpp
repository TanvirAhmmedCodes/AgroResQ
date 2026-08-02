#include "RouteOptimizationMenu.h"
#include <iostream>
#include <iomanip>

namespace AgroResQ
{
    namespace UI
    {
        RouteOptimizationMenu::RouteOptimizationMenu()
        {
            buildGraph();
        }

        void RouteOptimizationMenu::buildGraph()
        {
            graph.addVertex("ShelterA");
            graph.addVertex("ShelterB");
            graph.addVertex("ShelterC");
            graph.addVertex("Village1");
            graph.addVertex("Village2");
            graph.addVertex("Village3");
            graph.addVertex("Hospital");
            graph.addVertex("ReliefCenter");

            graph.addEdge("ShelterA", "Village1", 5);
            graph.addEdge("ShelterA", "Village2", 7);
            graph.addEdge("ShelterB", "Village1", 3);
            graph.addEdge("ShelterB", "Village3", 6);
            graph.addEdge("ShelterC", "Village2", 4);
            graph.addEdge("ShelterC", "Village3", 8);
            graph.addEdge("Village1", "Hospital", 2);
            graph.addEdge("Village2", "ReliefCenter", 3);
            graph.addEdge("Village3", "Hospital", 4);
            graph.addEdge("Village1", "Village2", 2);
            graph.addEdge("Village2", "Village3", 3);
        }

        void RouteOptimizationMenu::show()
        {
            int choice;
            do
            {
                std::cout << "\n=========================================\n";
                std::cout << "        ROUTE OPTIMIZATION SYSTEM\n";
                std::cout << "=========================================\n";
                std::cout << "1. Find Shortest Route\n";
                std::cout << "2. Display All Routes\n";
                std::cout << "3. Add Location\n";
                std::cout << "4. Add Route\n";
                std::cout << "0. Back\n";
                std::cout << "=========================================\n";
                std::cout << "Enter Choice: ";
                std::cin >> choice;

                switch (choice)
                {
                case 1:
                    findRoute();
                    break;
                case 2:
                    displayAllRoutes();
                    break;
                case 3:
                    addLocation();
                    break;
                case 4:
                    addRoute();
                    break;
                case 0:
                    break;
                default:
                    std::cout << "\nInvalid Choice.\n";
                }
            } while (choice != 0);
        }

        void RouteOptimizationMenu::findRoute()
        {
            std::string source, destination;

            std::cin.ignore();
            std::cout << "\nSource Location: ";
            getline(std::cin, source);
            std::cout << "Destination Location: ";
            getline(std::cin, destination);

            auto path = graph.findShortestPath(source, destination);

            if (path.empty())
            {
                std::cout << "\nNo route found between " << source << " and " << destination << "\n";
                return;
            }

            std::cout << "\nShortest Path from " << source << " to " << destination << ":\n";
            int totalDistance = 0;
            for (size_t i = 0; i < path.size(); i++)
            {
                std::cout << path[i];
                if (i < path.size() - 1)
                {
                    int weight = graph.getEdgeWeight(path[i], path[i + 1]);
                    totalDistance += weight;
                    std::cout << " -> (" << weight << ") -> ";
                }
            }
            std::cout << "\nTotal Distance: " << totalDistance << " units\n";
        }

        void RouteOptimizationMenu::displayAllRoutes()
        {
            std::cout << "\n=== ALL ROUTES IN SYSTEM ===\n";
            graph.displayGraph();
        }

        void RouteOptimizationMenu::addLocation()
        {
            std::string name;
            std::cin.ignore();
            std::cout << "\nLocation Name: ";
            getline(std::cin, name);

            graph.addVertex(name);
            std::cout << "\nLocation Added Successfully.\n";
        }

        void RouteOptimizationMenu::addRoute()
        {
            std::string from, to;
            int weight;

            std::cin.ignore();
            std::cout << "\nFrom: ";
            getline(std::cin, from);
            std::cout << "To: ";
            getline(std::cin, to);
            std::cout << "Distance: ";
            std::cin >> weight;

            graph.addEdge(from, to, weight);
            std::cout << "\nRoute Added Successfully.\n";
        }
    }
}