#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map> 
#include <climits>     // бесконечность
#include <algorithm>   // разворот вектора

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> cities;

public:
    // дорогу между двум€ городами в обе стороны
    void add_edge(const std::string& from, const std::string& to, int cost) {
        cities[from].push_back({ to, cost }); 
        cities[to].push_back({ from, cost }); 
    }

    // кратчайший путь между start и end
    std::vector<std::string> find_shortest_path(const std::string& start, const std::string& end) {
        // существуют ли города в графе
        if (cities.find(start) == cities.end() || cities.find(end) == cities.end()) {
            throw std::invalid_argument("ќдин из городов не найден!");
        }

        // мин рассто€ни€ до каждого города
        std::unordered_map<std::string, int> distances;
        // предыдущий город на пути
        std::unordered_map<std::string, std::string> prev;

        // все рассто€ни€ 99999999999
        for (const auto& city : cities) {
            distances[city.first] = INT_MAX;
        }
        distances[start] = 0; // до стартового города = 0

        // рассто€ние, город
        // —начала города с меньшим рассто€нием
        std::priority_queue<std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<>> pq;
        pq.push({ 0, start }); // со стартового города

        while (!pq.empty()) {
            // город с наименьшим текущим рассто€нием
            auto [current_dist, current_city] = pq.top();
            pq.pop();

            // если текущ расст > известного, пропускаем
            if (current_dist > distances[current_city]) continue;

            // перебор всех соседей текущего
            for (const auto& neighbor : cities[current_city]) {
                std::string next_city = neighbor.first;
                int cost = neighbor.second;

                // новое расст до соседнего
                int new_dist = current_dist + cost;

                // если нашли более короткий путь
                if (new_dist < distances[next_city]) {
                    distances[next_city] = new_dist; // ќбнов расст
                    prev[next_city] = current_city;  // предыдущий город
                    pq.push({ new_dist, next_city });  // + в очередь
                }
            }
        }

        // путь от end к start
        std::vector<std::string> path;
        if (distances[end] == INT_MAX) {
            return path; // путь не найден
        }

        std::string current = end;
        while (current != start) {
            path.push_back(current);
            current = prev[current]; // назад по цепочке
        }
        path.push_back(start); // + стартовый город
        std::reverse(path.begin(), path.end()); // разворот пути

        return path;
    }
};

int main()
{
    setlocale(LC_ALL, "");
    Graph g;
    g.add_edge("A", "B", 4);
    g.add_edge("A", "C", 2);
    g.add_edge("B", "C", 5);
    g.add_edge("C", "D", 3);

    try {
        auto path = g.find_shortest_path("A", "D");
        std::cout << " ратчайший путь: ";
        for (const auto& city : path) {
            std::cout << city << " ";
        }
        // ¬ывод: A C D
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "ќшибка: " << e.what() << std::endl;
    }

    return 0;
}