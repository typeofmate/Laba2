#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <functional> // ��� std::greater
struct Event {
    std::string description;
    //��� ���� �������
};

class EventManager {
private:
    std::map<int, Event> events; // �������� ������� �� ������� (���� � ��� �����)
    std::priority_queue<int,std::vector<int>,std::greater<int> > eventTimes;//��� ������������ �������

public:
    // ���������� �������
    void addEvent(int time, const Event& event) {
        events[time] = event; // ������� � map (����� ���������)
        eventTimes.push(time); // ���������� ������� � ������������ �������
    }

    // ��������� ���������� �������
    void processNextEvent() {
        if (eventTimes.empty()) {
            std::cout << "No events." << std::endl;
            return;
        }

        // ��������� ��������� ����� �� �������
        int nextTime = eventTimes.top();
        eventTimes.pop();

        // ����� ������� � map
        auto it = events.find(nextTime);
        if (it != events.end()) {
            std::cout << "Operating on event [" << nextTime << "]: "
                << it->second.description << std::endl;
            events.erase(it); // �������� ������������� �������
        }
        else {
            std::cout << "Event on " << nextTime << " not found." << std::endl;
        }
    }
};

int main() {
    EventManager manager;

    // ���������� �������
    manager.addEvent(10, { "Summit of the team" });
    manager.addEvent(5, { "Planning sprint" });
    manager.addEvent(15, { "Demonstration of project" });

    // ��������� ������� � ������� �������
    manager.processNextEvent(); // ����� 5
    manager.processNextEvent(); // ����� 10
    manager.processNextEvent(); // ����� 15
    manager.processNextEvent(); // ��� �������

    return 0;
}