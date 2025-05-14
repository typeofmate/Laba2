#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map> 
#include <climits>     // �������������
#include <algorithm>   // �������� �������

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> cities;

public:
    // ������ ����� ����� �������� � ��� �������
    void add_edge(const std::string& from, const std::string& to, int cost) {
        cities[from].push_back({ to, cost }); 
        cities[to].push_back({ from, cost }); 
    }

    // ���������� ���� ����� start � end
    std::vector<std::string> find_shortest_path(const std::string& start, const std::string& end) {
        // ���������� �� ������ � �����
        if (cities.find(start) == cities.end() || cities.find(end) == cities.end()) {
            throw std::invalid_argument("���� �� ������� �� ������!");
        }

        // ��� ���������� �� ������� ������
        std::unordered_map<std::string, int> distances;
        // ���������� ����� �� ����
        std::unordered_map<std::string, std::string> prev;

        // ��� ���������� 99999999999
        for (const auto& city : cities) {
            distances[city.first] = INT_MAX;
        }
        distances[start] = 0; // �� ���������� ������ = 0

        // ����������, �����
        // ������� ������ � ������� �����������
        std::priority_queue<std::pair<int, std::string>,
            std::vector<std::pair<int, std::string>>,
            std::greater<>> pq;
        pq.push({ 0, start }); // �� ���������� ������

        while (!pq.empty()) {
            // ����� � ���������� ������� �����������
            auto [current_dist, current_city] = pq.top();
            pq.pop();

            // ���� ����� ����� > ����������, ����������
            if (current_dist > distances[current_city]) continue;

            // ������� ���� ������� ��������
            for (const auto& neighbor : cities[current_city]) {
                std::string next_city = neighbor.first;
                int cost = neighbor.second;

                // ����� ����� �� ���������
                int new_dist = current_dist + cost;

                // ���� ����� ����� �������� ����
                if (new_dist < distances[next_city]) {
                    distances[next_city] = new_dist; // ����� �����
                    prev[next_city] = current_city;  // ���������� �����
                    pq.push({ new_dist, next_city });  // + � �������
                }
            }
        }

        // ���� �� end � start
        std::vector<std::string> path;
        if (distances[end] == INT_MAX) {
            return path; // ���� �� ������
        }

        std::string current = end;
        while (current != start) {
            path.push_back(current);
            current = prev[current]; // ����� �� �������
        }
        path.push_back(start); // + ��������� �����
        std::reverse(path.begin(), path.end()); // �������� ����

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
        std::cout << "���������� ����: ";
        for (const auto& city : path) {
            std::cout << city << " ";
        }
        // �����: A C D
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "������: " << e.what() << std::endl;
    }

    return 0;
}