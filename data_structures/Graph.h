#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <climits>

namespace AgroResQ
{
    namespace DataStructures
    {
        struct Edge
        {
            std::string destination;
            int weight;

            Edge(const std::string& dest, int w) : destination(dest), weight(w) {}
            bool operator>(const Edge& other) const { return weight > other.weight; }
        };

        class Graph
        {
        private:
            std::unordered_map<std::string, std::vector<Edge>> adjacencyList;

        public:
            Graph();

            void addVertex(const std::string& vertex);
            void addEdge(const std::string& from, const std::string& to, int weight);
            bool hasVertex(const std::string& vertex) const;
            bool hasEdge(const std::string& from, const std::string& to) const;
            std::vector<std::string> getVertices() const;
            std::vector<Edge> getNeighbors(const std::string& vertex) const;
            int getEdgeWeight(const std::string& from, const std::string& to) const;
            void removeVertex(const std::string& vertex);
            void removeEdge(const std::string& from, const std::string& to);

            std::unordered_map<std::string, int> dijkstra(const std::string& source);
            std::vector<std::string> findShortestPath(const std::string& source, const std::string& destination);
            void displayGraph() const;
        };
    }
}