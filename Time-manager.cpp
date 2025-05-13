#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <functional> // Для std::greater
struct Event {
    std::string description;
    //Доп поля события
};

class EventManager {
private:
    std::map<int, Event> events; // Хранение событий по времени (ключ и его время)
    std::priority_queue<int,std::vector<int>,std::greater<int> > eventTimes;//для минимального времени

public:
    // Добавление события
    void addEvent(int time, const Event& event) {
        events[time] = event; // Вставка в map (время уникально)
        eventTimes.push(time); // Добавление времени в приоритетную очередь
    }

    // Обработка ближайшего события
    void processNextEvent() {
        if (eventTimes.empty()) {
            std::cout << "No events." << std::endl;
            return;
        }

        // Извлекаем ближайшее время из очереди
        int nextTime = eventTimes.top();
        eventTimes.pop();

        // Поиск события в map
        auto it = events.find(nextTime);
        if (it != events.end()) {
            std::cout << "Operating on event [" << nextTime << "]: "
                << it->second.description << std::endl;
            events.erase(it); // Удаление обработанного события
        }
        else {
            std::cout << "Event on " << nextTime << " not found." << std::endl;
        }
    }
};

int main() {
    EventManager manager;

    // Добавление событий
    manager.addEvent(10, { "Summit of the team" });
    manager.addEvent(5, { "Planning sprint" });
    manager.addEvent(15, { "Demonstration of project" });

    // Обработка событий в порядке времени
    manager.processNextEvent(); // Время 5
    manager.processNextEvent(); // Время 10
    manager.processNextEvent(); // Время 15
    manager.processNextEvent(); // Нет событий

    return 0;
}