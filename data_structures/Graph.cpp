#include "Graph.h"
#include <iostream>
#include <algorithm>
#include <climits>

namespace AgroResQ
{
    namespace DataStructures
    {
        Graph::Graph() {}

        void Graph::addVertex(const std::string& vertex)
        {
            if (adjacencyList.find(vertex) == adjacencyList.end())
            {
                adjacencyList[vertex] = std::vector<Edge>();
            }
        }

        void Graph::addEdge(const std::string& from, const std::string& to, int weight)
        {
            if (adjacencyList.find(from) == adjacencyList.end())
                addVertex(from);
            if (adjacencyList.find(to) == adjacencyList.end())
                addVertex(to);

            adjacencyList[from].push_back(Edge(to, weight));
        }

        bool Graph::hasVertex(const std::string& vertex) const
        {
            return adjacencyList.find(vertex) != adjacencyList.end();
        }

        bool Graph::hasEdge(const std::string& from, const std::string& to) const
        {
            if (adjacencyList.find(from) == adjacencyList.end())
                return false;

            for (const auto& edge : adjacencyList.at(from))
            {
                if (edge.destination == to)
                    return true;
            }
            return false;
        }

        std::vector<std::string> Graph::getVertices() const
        {
            std::vector<std::string> vertices;
            for (const auto& pair : adjacencyList)
            {
                vertices.push_back(pair.first);
            }
            return vertices;
        }

        std::vector<Edge> Graph::getNeighbors(const std::string& vertex) const
        {
            if (adjacencyList.find(vertex) == adjacencyList.end())
                return std::vector<Edge>();
            return adjacencyList.at(vertex);
        }

        int Graph::getEdgeWeight(const std::string& from, const std::string& to) const
        {
            if (adjacencyList.find(from) == adjacencyList.end())
                return -1;

            for (const auto& edge : adjacencyList.at(from))
            {
                if (edge.destination == to)
                    return edge.weight;
            }
            return -1;
        }

        void Graph::removeVertex(const std::string& vertex)
        {
            if (adjacencyList.find(vertex) == adjacencyList.end())
                return;

            adjacencyList.erase(vertex);

            for (auto& pair : adjacencyList)
            {
                auto& edges = pair.second;
                edges.erase(
                    std::remove_if(edges.begin(), edges.end(),
                        [&vertex](const Edge& edge) { return edge.destination == vertex; }),
                    edges.end()
                );
            }
        }

        void Graph::removeEdge(const std::string& from, const std::string& to)
        {
            if (adjacencyList.find(from) == adjacencyList.end())
                return;

            auto& edges = adjacencyList[from];
            edges.erase(
                std::remove_if(edges.begin(), edges.end(),
                    [&to](const Edge& edge) { return edge.destination == to; }),
                edges.end()
            );
        }

        std::unordered_map<std::string, int> Graph::dijkstra(const std::string& source)
        {
            std::unordered_map<std::string, int> distances;
            std::unordered_map<std::string, bool> visited;

            for (const auto& pair : adjacencyList)
            {
                distances[pair.first] = INT_MAX;
                visited[pair.first] = false;
            }

            if (distances.find(source) == distances.end())
                return distances;

            distances[source] = 0;

            auto compare = [&](const std::string& a, const std::string& b) {
                return distances[a] > distances[b];
            };

            std::priority_queue<std::string, std::vector<std::string>, decltype(compare)> pq(compare);
            pq.push(source);

            while (!pq.empty())
            {
                std::string current = pq.top();
                pq.pop();

                if (visited[current]) continue;
                visited[current] = true;

                for (const auto& edge : adjacencyList[current])
                {
                    if (!visited[edge.destination])
                    {
                        int newDist = distances[current] + edge.weight;
                        if (newDist < distances[edge.destination])
                        {
                            distances[edge.destination] = newDist;
                            pq.push(edge.destination);
                        }
                    }
                }
            }

            return distances;
        }

        std::vector<std::string> Graph::findShortestPath(const std::string& source, const std::string& destination)
        {
            std::vector<std::string> path;
            std::unordered_map<std::string, int> distances;
            std::unordered_map<std::string, std::string> previous;
            std::unordered_map<std::string, bool> visited;

            for (const auto& pair : adjacencyList)
            {
                distances[pair.first] = INT_MAX;
                visited[pair.first] = false;
                previous[pair.first] = "";
            }

            if (distances.find(source) == distances.end() || distances.find(destination) == distances.end())
                return path;

            distances[source] = 0;

            auto compare = [&](const std::string& a, const std::string& b) {
                return distances[a] > distances[b];
            };

            std::priority_queue<std::string, std::vector<std::string>, decltype(compare)> pq(compare);
            pq.push(source);

            while (!pq.empty())
            {
                std::string current = pq.top();
                pq.pop();

                if (visited[current]) continue;
                visited[current] = true;

                if (current == destination) break;

                for (const auto& edge : adjacencyList[current])
                {
                    if (!visited[edge.destination])
                    {
                        int newDist = distances[current] + edge.weight;
                        if (newDist < distances[edge.destination])
                        {
                            distances[edge.destination] = newDist;
                            previous[edge.destination] = current;
                            pq.push(edge.destination);
                        }
                    }
                }
            }

            if (previous[destination].empty() && source != destination)
                return path;

            std::string current = destination;
            while (current != source)
            {
                path.insert(path.begin(), current);
                current = previous[current];
                if (current.empty()) break;
            }
            if (!current.empty())
                path.insert(path.begin(), source);

            return path;
        }

        void Graph::displayGraph() const
        {
            for (const auto& pair : adjacencyList)
            {
                std::cout << pair.first << " -> ";
                for (const auto& edge : pair.second)
                {
                    std::cout << edge.destination << "(" << edge.weight << ") ";
                }
                std::cout << "\n";
            }
        }
    }
}